// Health Regen: an example mod for the Sin and Punishment recomp.
// While you're hurt, your health slowly fills back up.

#include "modding.h"
#include "recompconfig.h"
#include "snp.h"

static u32 frame_count = 0;

// func_8004C55C is the game's controller read. It runs once a frame, so
// it's a good place to run code every frame.
// RECOMP_HOOK runs our function right before the game's function. The
// game's function still runs as normal after.
RECOMP_HOOK("func_8004C55C")
void health_regen_on_frame(void) {
    // "regen_frames" is the option from mod.toml. You can change it in
    // the Mods menu.
    u32 frames_per_point = recomp_get_config_u32("regen_frames");

    frame_count++;
    if (frame_count < frames_per_point) {
        return;
    }
    frame_count = 0;

    // Only when alive and hurt. At 0 you're dead, so leave it alone.
    if (SNP_HEALTH > 0 && SNP_HEALTH < SNP_HEALTH_FULL) {
        SNP_HEALTH++;
    }
}
