#pragma once
#include "Level.h"
#include "PlayerObject.h"
#include "SoundManager.h"

class Ability {
    private:
        Level* level;
        float fireballCooldown = 3.0f;
        float trapCooldown = 3.0f;
        float dashCooldown = 3.0f;
        float TNTCooldown = 3.0f;
        float teleportCooldown = 3.0f;
        float bolaCooldown = 3.0f;
        float cleaveCooldown = 3.0f;
        float fireballLifetime = 5.0f;
        float teleportLifetime = 5.0f;
        float bolaLifetime = 5.0f;
        float cleaveLifetime = 5.0f;
        float dashDuration = 1.5f;

    public:
        Ability();

        //Set
        void SetFireballCooldown(float cooldown);
        void SetTrapCooldown(float cooldown);
        void SetDashCooldown(float cooldown);
        void SetTNTCooldown(float cooldown);
        void SetTeleportCooldown(float cooldown);
        void SetBolaCooldown(float cooldown);
        void SetCleaveCooldown(float cooldown);
        void SetFireballLifetime(float Lifetime);
        void SetTeleportLifetime(float Lifetime);
        void SetBolaLifetime(float Lifetime);
        void SetCleaveLifetime(float Lifetime);
        void SetDashDuration(float Duration);
        void SetCurrLevel(Level* level);

        //Get
        float GetFireballCooldown();
        float GetTrapCooldown();
        float GetDashCooldown();
        float GetTNTCooldown();
        float GetTeleportCooldown();
        float GetBolaCooldown();
        float GetCleaveCooldown();
        float GetFireballLifetime();
        float GetTeleportLifetime();
        float GetBolaLifetime();
        float GetCleaveLifetime();
        float GetDashDuration();

        //Keybinding
        void UsingAbilityKeyDown(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button);
        void UsingAbilityKeyUp(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button);


        //Ability
        void AimFireball(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button);
        void ShootFireball(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button);

        void AimTeleport(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button);
        void ShootTeleport(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button);

        void AimBola(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button);
        void ShootBola(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button);

        void AimCleave(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button);
        void ShootCleave(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button);

        void Trap(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button);
        void Dash(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button);
        void TNT(PlayerObject* player, int numPlayer, PlayerObject::AbilityButton button);
};


