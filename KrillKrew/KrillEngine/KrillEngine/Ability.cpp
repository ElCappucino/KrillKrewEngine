#include "Ability.h"

Ability::Ability():level(nullptr) {

}

//Set
void Ability::SetFireballCooldown(float cooldown) {
    this->fireballCooldown = cooldown;
}
void Ability::SetTrapCooldown(float cooldown) {
    this->trapCooldown = cooldown;
}

void Ability::SetDashCooldown(float cooldown) {
    this->dashCooldown = cooldown;
}

void Ability::SetTNTCooldown(float cooldown) {
    this->TNTCooldown = cooldown;
}

void Ability::SetTeleportCooldown(float cooldown) {
    this->teleportCooldown = cooldown;
}
void Ability::SetBolaCooldown(float cooldown) {
    this->bolaCooldown = cooldown;
}
void Ability::SetCleaveCooldown(float cooldown) {
    this->cleaveCooldown = cooldown;
}
void Ability::SetFireballLifetime(float lifetime) {
    this->fireballLifetime = lifetime;
}
void Ability::SetTeleportLifetime(float lifetime) {
    this->teleportLifetime = lifetime;
}
void Ability::SetBolaLifetime(float lifetime) {
    this->bolaLifetime = lifetime;
}
void Ability::SetCleaveLifetime(float lifetime) {
    this->cleaveLifetime = lifetime;
}
void Ability::SetDashDuration(float Duration) {
    this->dashDuration = Duration;
}

void Ability::SetCurrLevel(Level* level) {
    this->level = level;
}

//Get
float Ability::GetFireballCooldown() {
    return fireballCooldown;
}
float Ability::GetTrapCooldown() {
    return trapCooldown;
}
float Ability::GetDashCooldown() {
    return dashCooldown;
}
float Ability::GetTNTCooldown() {
    return TNTCooldown;
}
float Ability::GetTeleportCooldown() {
    return teleportCooldown;
}
float Ability::GetBolaCooldown() {
    return bolaCooldown;
}
float Ability::GetCleaveCooldown() {
    return cleaveCooldown;
}
float Ability::GetFireballLifetime() {
    return fireballLifetime;
}
float Ability::GetTeleportLifetime() {
    return teleportLifetime;
}
float Ability::GetBolaLifetime() {
    return bolaLifetime;
}
float Ability::GetCleaveLifetime() {
    return cleaveLifetime;
}
float Ability::GetDashDuration() {
    return dashDuration;
}

//Keybinding
void Ability::UsingAbilityKeyDown(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button)
{
    PlayerObject::Ability idAbility = player->GetAbilityByButton(button);
    if (player->GetCooldown(button) <= 0 && !player->GetIsBurning() && !player->GetIsStun())
    {
        switch (idAbility)
        {
        case PlayerObject::Ability::Fireball:
            if (!player->GetIsAiming())
            {
                AimFireball(player, numPlayer, button);
            }
            break;

        case PlayerObject::Ability::Trap:
            Trap(player, numPlayer, button);
            KrillSoundManager::SoundManager::GetInstance()->PlaySFX("Jellyfish_Placed", false);
            break;

        case PlayerObject::Ability::Dash:
            Dash(player, numPlayer, button);
            break;

        case PlayerObject::Ability::TNT:
            if (!player->GetIsTNT())
            {
                TNT(player, numPlayer, button);
                KrillSoundManager::SoundManager::GetInstance()->PlaySFX("Landmine_Placed", false);
            }
            else if (player->GetIsTNT())
            {
                for (TrapObject* trap : player->GetOwningTrap())
                {
                    if (trap->GetType() == TrapObject::TypeTrap::Tnt)
                    {
                        KrillSoundManager::SoundManager::GetInstance()->PlaySFX("Landmine_Explode", false);
                        trap->ExplodeTileInRange();
                        trap->ChangeAnimationState(TrapObject::AnimationState::Collide);
                        KK_TRACE("Press Again");
                        trap->isActivate = true;
                        player->SetAbilityCooldown(button, 3);
                        player->SetIsTNT(false);
                        player->RemoveOwningTrap(trap);
                    }
                }
            }
            break;

        case PlayerObject::Ability::Teleport:
            if (!player->GetIsAiming())
            {
                if (player->GetIsShooting())
                {
                    for (ProjectileObject* projectile : player->GetOwningProjectile())
                    {
                        if (projectile->GetType() == ProjectileObject::TypeProjectile::Teleport)
                        {
                            KrillSoundManager::SoundManager::GetInstance()->PlaySFX("Teleport_Hit", false);
                            player->SetPosition(projectile->getPos());
                            player->SetIsShooting(false);
                            projectile->SetIsActive(false);
                            player->SetAbilityCooldown(button, 6);
                            player->RemoveOwningProjectile(projectile);
                        }
                    }
                }
                else
                {
                    AimTeleport(player, numPlayer, button);
                }
            }
            break;

        case PlayerObject::Ability::Bola:
            if (!player->GetIsAiming())
            {
                AimBola(player, numPlayer, button);
            }
            break;

        case PlayerObject::Ability::Cleave:
            if (!player->GetIsAiming())
            {
                AimCleave(player, numPlayer, button);
            }
            break;
        }
    }
}

void Ability::UsingAbilityKeyUp(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button)
{
    PlayerObject::Ability idAbility = player->GetAbilityByButton(button);

    if (player->GetCooldown(button) <= 0)
    {
        switch (idAbility)
        {
        case PlayerObject::Ability::Fireball:
            if (player->GetIsAiming())
            {
                if (player->GetHoldingProjectile() == ProjectileObject::TypeProjectile::Fireball)
                {
                    ShootFireball(player, numPlayer, button);
                }
            }
            break;

        case PlayerObject::Ability::Teleport:
            if (player->GetIsAiming())
            {
                if (player->GetHoldingProjectile() == ProjectileObject::TypeProjectile::Teleport)
                {
                    ShootTeleport(player, numPlayer, button);
                    KrillSoundManager::SoundManager::GetInstance()->PlaySFX("Teleport_Throwing", false);
                }
            }
            break;

        case PlayerObject::Ability::Bola:
            if (player->GetIsAiming())
            {
                if (player->GetHoldingProjectile() == ProjectileObject::TypeProjectile::Bola)
                {
                    ShootBola(player, numPlayer, button);
                    KrillSoundManager::SoundManager::GetInstance()->PlaySFX("Bola_Throwing", false);
                }
            }
            break;
        }
    }
}

//Fireball
void Ability::AimFireball(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button)
{
    player->SetVelocity(0, 0, false, false);
    player->SetIsAiming(true);
    player->SetHoldingProjectile(ProjectileObject::TypeProjectile::Fireball);

    ProjectileObject* projectile = new ProjectileObject();
    level->SetProjectileAnimation(projectile, "Bomb_Explode");
    level->SetSprite(projectile, "Bomb");
    projectile->SetPosition(player->getPos());
    projectile->SetSize(256.f, -256.f);
    projectile->SetLifeTime(9999);
    projectile->SetOwner(player);
    projectile->SetType(ProjectileObject::TypeProjectile::Fireball);
    projectile->SetCanKnockback(true);
    projectile->SetIsCanStun(true);
    projectile->SetIsShooting(false);

    std::cout << "Owner " << projectile->GetOwner()->GetPlayerNumber() << std::endl;
    level->AddEntityToScene(projectile);
    player->AddOwningProjectile(projectile);
}

void Ability::ShootFireball(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button)
{
    player->SetIsAiming(false);

    for (ProjectileObject* projectile : player->GetOwningProjectile())
    {
        if (projectile->GetType() == ProjectileObject::TypeProjectile::Fireball)
        {
            projectile->SetLifeTime(fireballLifetime);
            projectile->SetIsShooting(true);
            player->SetHoldingProjectile(0);
        }
    }

    player->SetAbilityCooldown(button, fireballCooldown);
}

//Teleport
void Ability::AimTeleport(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button)
{
    player->SetVelocity(0, 0, false, false);
    player->SetIsAiming(true);
    player->SetHoldingProjectile(ProjectileObject::TypeProjectile::Teleport);

    ProjectileObject* projectile = new ProjectileObject();
    level->SetProjectileAnimation(projectile, "Teleport_Explode");
    level->SetSprite(projectile, "Teleport");
    projectile->SetPosition(player->getPos());
    projectile->SetSize(256.f, -256.f);
    projectile->SetLifeTime(9999);
    projectile->SetOwner(player);
    projectile->SetType(ProjectileObject::TypeProjectile::Teleport);
    projectile->SetCanKnockback(false);
    projectile->SetIsCanStun(false);
    projectile->SetIsShooting(false);

    std::cout << "Owner " << projectile->GetOwner()->GetPlayerNumber() << std::endl;

    level->AddEntityToScene(projectile);
    player->AddOwningProjectile(projectile);
}

void Ability::ShootTeleport(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button)
{
    if (!player->GetIsShooting())
    {
        player->SetIsShooting(true);
        player->SetIsAiming(false);

        for (ProjectileObject* projectile : player->GetOwningProjectile())
        {
            if (projectile->GetType() == ProjectileObject::TypeProjectile::Teleport)
            {
                projectile->SetLifeTime(teleportLifetime);
                projectile->SetIsShooting(true);
                player->SetHoldingProjectile(0);
            }
        }
    }
}

//Bola
void Ability::AimBola(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button)
{
    player->SetVelocity(0, 0, false, false);
    player->SetIsAiming(true);
    player->SetHoldingProjectile(ProjectileObject::TypeProjectile::Bola);

    ProjectileObject* projectile = new ProjectileObject();
    level->SetProjectileAnimation(projectile, "Stun_Explode");
    level->SetSprite(projectile, "Bola");
    projectile->SetPosition(player->getPos());
    projectile->SetSize(256.f, -256.f);
    projectile->SetLifeTime(9999);
    projectile->SetOwner(player);
    projectile->SetType(ProjectileObject::TypeProjectile::Bola);
    projectile->SetCanKnockback(false);
    projectile->SetIsCanStun(true);
    projectile->SetIsShooting(false);

    std::cout << "Owner " << projectile->GetOwner()->GetPlayerNumber() << std::endl;

    level->AddEntityToScene(projectile);
    player->AddOwningProjectile(projectile);
}

void Ability::ShootBola(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button)
{
    player->SetIsAiming(false);

    for (ProjectileObject* projectile : player->GetOwningProjectile())
    {
        if (projectile->GetType() == ProjectileObject::TypeProjectile::Bola)
        {
            projectile->SetLifeTime(bolaLifetime);
            projectile->SetIsShooting(true);
            player->SetHoldingProjectile(0);
        }
    }

    player->SetAbilityCooldown(button, bolaCooldown);
}

//Cleave
void Ability::AimCleave(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button)
{
    player->SetVelocity(0, 0, false, false);
    player->SetIsAiming(true);
    player->SetHoldingProjectile(ProjectileObject::TypeProjectile::Cleave);
}

void Ability::ShootCleave(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button)
{
    player->SetIsAiming(false);

    ProjectileObject* projectile = new ProjectileObject();
    level->SetSprite(projectile, "Cleave");
    projectile->SetPosition(player->getPos());
    projectile->SetSize(256.f, -256.f);
    projectile->SetOwner(player);
    projectile->SetType(ProjectileObject::TypeProjectile::Cleave);
    projectile->SetCanKnockback(false);
    projectile->SetIsCanStun(true);
    projectile->SetIsShooting(false);

    std::cout << "Owner " << projectile->GetOwner()->GetPlayerNumber() << std::endl;

    level->AddEntityToScene(projectile);
    player->AddOwningProjectile(projectile);

    projectile->SetLifeTime(cleaveLifetime);
    projectile->SetIsShooting(true);
    player->SetHoldingProjectile(0);
    projectile->SetLifeTime(1);

    float veloX = player->GetCurrentDirection().x;
    float veloY = player->GetCurrentDirection().y;
    float angle = atan2(-player->GetCurrentDirection().y, player->GetCurrentDirection().x);

    float absSizeX = abs(projectile->getSize().x);

    if (angle < -3.14f / 2.f || angle > 3.14f / 2.f)
    {
        projectile->SetSize(-absSizeX, projectile->getSize().y);

        if (angle > 0)
            angle = -(3.14f - angle);
        else
            angle = 3.14f + angle;
    }
    else
    {
        projectile->SetSize(absSizeX, projectile->getSize().y);
    }

    bool positiveX = veloX > 0.f;
    bool positiveY = veloY < 0.f;

    projectile->SetPosition(player->getPos() + (projectile->GetVelocity() * glm::vec3(15.f, 15.f, 0.f)));
    projectile->SetRotation(angle);
    projectile->SetVelocity(abs(veloX), abs(veloY), positiveX, positiveY);

    player->SetAbilityCooldown(button, cleaveCooldown);

    KrillSoundManager::SoundManager::GetInstance()->PlaySFX("Cleave_Slash", false);
}

//Trap
void Ability::Trap(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button)
{
    player->ChangeAnimationState(PlayerObject::AnimationState::PlaceItem);
    player->SetAbilityCooldown(button, trapCooldown);

    TrapObject* trap = new TrapObject();
    level->SetSprite(trap, "Trap");
    trap->SetPosition(player->getPos());
    trap->SetSize(128.f, -128.f);
    trap->SetPlayerNumber(player->GetPlayerNumber());
    trap->SetType(TrapObject::TypeTrap::Trap);
    trap->SetIsActive(true);
    level->SetTrapAnimation(trap, "Trap", "Trap_Explode");

    level->AddEntityToScene(trap);
    player->AddOwningTrap(trap);
}

//Dash
void Ability::Dash(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button)
{
    player->SetAbilityCooldown(button, dashCooldown);
    player->SetIsDashing(true);
    player->SetDashDuration(dashDuration);
}

//TNT
void Ability::TNT(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button)
{
    player->SetIsTNT(true);
    player->ChangeAnimationState(PlayerObject::AnimationState::PlaceItem);

    TrapObject* tnt = new TrapObject();
    level->SetSprite(tnt, "TNT");
    tnt->SetPosition(player->getPos());
    tnt->SetSize(128.f, -128.f);
    tnt->GetCollider()->setColliderSize(glm::vec3(500.f, 500.f, 0));
    tnt->SetPlayerNumber(player->GetPlayerNumber());
    tnt->SetType(TrapObject::TypeTrap::Tnt);
    level->SetTrapAnimation(tnt, "TNT", "Landmine_Explode");
    tnt->SetOwner(player);
    level->AddEntityToScene(tnt);
    player->AddOwningTrap(tnt);
}