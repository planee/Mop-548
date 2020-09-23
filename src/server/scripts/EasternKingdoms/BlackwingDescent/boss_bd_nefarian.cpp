#include "ScriptPCH.h"
#include "blackwing_descent.h"
#include "Vehicle.h"
#include "Unit.h"
#include "Object.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CombatAI.h"
#include "PassiveAI.h"
#include "ObjectMgr.h"
#include "SpellInfo.h"
#include "SpellScript.h"
#include "Vehicle.h"
#include "VehicleDefines.h"
#include "Spell.h"
#include "Player.h"
#include "Map.h"
#include "InstanceScript.h"
#include "Transport.h"
#include "MapManager.h"
#include "UpdateData.h"
#include "WorldPacket.h"
#include "World.h"

enum NefYells
{
/*
20072 - cowards! face the broodmother or face dire consequences!
Phase1
20073 - See how the shadowflame animates the bones? They fight at my command!

Phase2
20082 - Curse you mortals! Such callous disregard for one's possessions must be met with extreme force.
20075 - I hope you can swim... in molten lava! (p2).

Phase 3
20077 - I have tried to be an accomodating host, but you simply will not die. Time to throw all pretense aside and just KILL YOU ALL!

Shadowflame 
20074 - Flesh turns to ash!

Killing a player 
20079 - It has been a pleasure!
20081 - You really have to want it!

Death
20083 - Defeat has never tasted so bitter...
*/

    // Nefarian
    SAY_AVOID_WIPE                  = 0,
    SAY_AGGRO                       = 1,
    SAY_AIR_PHASE                   = 2,
    SAY_AIR_PHASE_2                 = 3,
    SAY_FINAL_PHASE                 = 4,
    SAY_SHADOWFLAME                 = 5,
    SAY_KILL                        = 6,
    SAY_DEATH                       = 7
};

enum IntroYells
{
/*
Intro
20066 - Ha ha ha ha ha! The heroes have made it to the glorious finale! I take it you are in good spirits? Prepared for the final battle? Then gaze now upon my ultimate creation! RISE, SISTER!
20070 - Behold, the Broodmother... Onyxia... REBORN. Perhaps my finest work.
20071 - My dearest sibling... do you hunger? THEN FEAST UPON OUR ENEMIES!
*/
    SAY_INTRO_1                     = 0,
    SAY_INTRO_2                     = 1,
    SAY_INTRO_3                     = 2,
};

enum Spells
{
    // Children of Deathwing - if < 50y from each other.
    SPELL_CHILDREN_OF_DEATHWING_NEF = 78620,
    SPELL_CHILDREN_OF_DEATHWING_ONY = 78619,

    // Nefarian
        // Ground
    SPELL_ELECTROCUTE          = 81272, // Every 10% of Nef life, on all p, needs radius 100 y. Used by Nefarian's Lightning Machine(51089) actually, but boss can do it just as good.
    SPELL_SHADOWFLAME_BREATH   = 77826, // Does 78122 and animates bone warriors in 60y. Script eff on 3.
    SPELL_ANIMATE_BONES        = 78122, // Not used alone but with sf breath.
    SPELL_HAIL_OF_BONES        = 78679, // Summons a bone warrior plus damage, beginning of p1.
    SPELL_TAIL_LASH            = 77827, // For those standing behind :P
    SPELL_SHADOWBLAZE_SPARK    = 81031, // Last phase, summons npc Shadowblaze Flashpoint.

        // Air                     
    SPELL_SHADOWFLAME_BARRAGE           = 78621, // While flying, random.
    SPELL_H_EXPLOSIVE_CINDERS_PERIODIC  = 79339, // Only HEROIC! 8 sec.
    SPELL_H_EXPLOSIVE_CINDERS_SUMM_DMG  = 79347, // Only HEROIC! does damage after 8 sec. of periodic, on removal (spell_linked_spell needed).

    SPELL_SHADOW_COWARDICE     = 79353, // If fight resets and people in area -> wipe.

        // Heroic Dominion Mechanic.
    SPELL_DOMINION             = 79318, // Controlled by Nef - grants ability bar.
    SPELL_DOMINION_IMMUN       = 95900, // Immunities.
    SPELL_DOMINION_DUMMY       = 94211, // Faction dummy.

    SPELL_SIPHON_POWER         = 79319, // On Abil bar - on cast -> Stolen.
    SPELL_STOLEN_POWER         = 80627, // Buff from Siphon, needs spell_linked_spell on that cast.
    SPELL_FREE_MIND            = 79323, // Works already!

    // Onyxia - Lightning Discharge needs research.
    SPELL_ONYXIA_DISCHARGE_BAR = 78949,
    SPELL_INCREASE_BAR         = 98734, // +1 power on discharge bar.

    SPELL_LIGHTNING_DISCHARGE  = 77944,

    // Anim Bone Warriors
    SPELL_NO_REGEN             = 78725,
    SPELL_NO_REGEN2            = 72242,
    SPELL_EMPOWER              = 79329, // Aura applied on summoned.
    SPELL_HURL_BONE            = 81586,
    SPELL_DIE_VISUAL           = 57626, // Just some die visual spell. They are not actually dead.

    // Chromatic Prototype
    SPELL_NOVA                 = 80734, // Needs interr or wipes raid, periodic trigger aura.

    // Shadowblaze Flashpoint
    SPELL_FIREBRUSH_AURA       = 79396  // Aura on summ, 81007 every sec and 78122, reanimating bone warrs. See SPELL_SHADOWBLAZE_SPARK.
};

enum Phases
{
    PHASE_NULL = 0,
    PHASE_INTRO,
    PHASE_GROUND,
    PHASE_FLIGHT,
    PHASE_FINAL
};

enum Events
{
// Nefarian
    // Intro
    EVENT_INTRO_1 = 1,
    EVENT_INTRO_2,
    EVENT_INTRO_3,
    EVENT_SUMMON_ONYXIA,
    EVENT_SUMMON_NEFARIAN,
	EVENT_NOT_PREPARE,

    EVENT_INTRO,
    EVENT_INTRO2,
    EVENT_HAIL_OF_BONES,
    EVENT_MOVE,
    EVENT_LANDING,

    EVENT_ELECTROCUTE,

    // Ground phase
    EVENT_SHADOWFLAME_BREATH,
    EVENT_SHADOW_COWARDICE,
    EVENT_TAIL_LASH,

    EVENT_LIFTOFF,
    EVENT_FLIGHT,
    EVENT_AIR,
 
    // Air phase
    EVENT_SHADOWFLAME_BARRAGE,
    EVENT_SUMMON_CHROMATIC,
    EVENT_LAND,
    EVENT_RETURN,
    EVENT_GROUND,

    // Final phase
    EVENT_SHADOWBLAZE,
    EVENT_REVIVE_SKELETONS,

// Onyxia
   EVENT_SF_BREATH,
   EVENT_LIGHTNING_DISCHARGE,
   EVENT_TAL_LASH,
   EVENT_INCREASE_BAR
};

enum Npc
{
    NPC_NEFARIAN_INTRO = 41379,
    NPC_CHROMATIC_PROTO = 41948,
    NPC_ANIM_BONE_WARR = 41918, 
    MOB_SHADOWBLAZE = 42596,
};

Position const NefarianPositions[3] =
{
    {-135.795151f, 15.569847f, 73.165909f, 4.646072f}, // Intro
    {-129.176636f, -10.488489f, 73.079071f, 5.631739f}, // Ground
    {-106.186249f, -18.533386f, 72.798332f, 1.555510f}, // Air
};

Position ChromaticPositions[3] =
{
    {-107.213f, -224.62f, 7.70235f, 3.1416f}, // Normal position.
    {-107.213f, -224.62f, -8.32f, 3.1416f}, // Intro position.
    {-107.213f, -224.62f, -6.8679f, 3.1416f}, // Position for p2.
};

Position elevator_pos1 = { -107.413f, -224.544f, 7.03009f, 6.14492f };
Position elevator_pos2 = { -107.413f, -224.544f, 2.03009f, 6.14492f };

Position const npc_chromatic[3] = {	
	{-127.232f, -250.124f , 12.219f, 2.493f },
	{-121.360f, -193.587f, 12.219f, 0.441f},
	{-73.828f, -229.345f, 12.219f, 4.586f}	
};



Position const firefloor[353] = 
{
	{ -145.601f, -252.776f, 5.15445f, 2.57341f },
	{ -147.843f, -248.743f, 5.15445f, 2.42419f },
	{ -150.208f, -252.218f, 5.15445f, 3.04858f },
	{ -152.13f, -247.703f, 5.15445f, 3.01716f },
	{ -149.141f, -245.479f, 5.15445f, 1.87834f },
	{ -145.295f, -245.373f, 5.15445f, 3.31169f },
	{ -146.655f, -241.997f, 5.15445f, 3.13497f },
	{ -149.845f, -241.989f, 5.15445f, 3.1389f },
	{ -153.014f, -244.176f, 5.15445f, 3.1389f },
	{ -155.715f, -241.283f, 5.15445f, 3.00538f },
	{ -150.757f, -239.233f, 5.15445f, 2.32601f },
	{ -147.712f, -237.912f, 5.15445f, 3.87718f },
	{ -148.746f, -233.872f, 5.15445f, 4.855f },
	{ -150.909f, -234.182f, 5.15445f, 4.855f },
	{ -154.594f, -234.739f, 5.15445f, 4.86285f },
	{ -157.232f - 236.7f,   5.15445f, 5.01207f },
	{ -157.743f, -232.003f, 5.15445f, 3.76722f },
	{ -158.481f, -227.124f, 5.15445f, 3.2842f },
	{ -154.7f,	 -228.881f,	5.15445f, 4.69792f },
	{ -150.233f, -228.945f, 5.15445f, 4.69792f },
	{ -149.872f, -224.227f, 5.15445f, 2.86794f },
	{ -153.42f,	 -223.653f, 5.15445f, 3.07607f },
	{ -157.691f, -222.261f, 5.15445f, 3.85361f },
	{ -158.906f, -217.965f, 5.15445f, 3.00931f },
	{ -153.599f, -219.876f, 5.15445f, 3.5748f },
	{ -150.098f, -216.809f, 5.15445f, 1.79194f },
	{ -154.794f, -214.985f, 5.15445f, 1.82336f },
	{ -157.652f, -212.522f, 5.15342f, 1.97651f },
	{ -154.301f, -209.447f, 5.15342f, 1.97651f },
	{ -148.669f, -211.239f, 5.15342f, 1.86656f },
	{ -154.853f, -205.585f, 5.15342f, 2.17679f },
	{ -149.181f, -206.807f, 5.15342f, 1.16363f },
	{ -146.121f, -206.897f, 5.15342f, 1.44637f },
	{ -152.206f, -202.456f, 5.15342f, 1.67806f },
	{ -149.511f, -199.861f, 5.15342f, 1.67806f },
	{ -146.893f, -203.499f, 5.15342f, 2.53807f },
	{ -148.163f, -196.482f, 5.15342f, 2.3535f },
	{ -146.845f, -191.453f, 5.15342f, 2.3535f },
	{ -143.027f, -194.478f, 5.15344f, 0.947641f },
	{ -139.802f, -196.963f, 5.15344f, 2.48309f },
	{ -137.978f, -192.313f, 5.15344f, 2.36528f },
	{ -142.5f,	 -189.629f, 5.15344f, 2.51451f },
	{ -141.024f, -185.726f, 5.15344f, 2.15323f },
	{ -137.031f, -187.557f, 5.15344f, 0.747364f },
	{ -133.202f, -188.814f, 5.15344f, 0.814123f },
	{ -129.909f, -187.311f, 5.15344f, 0.869101f },
	{ -134.761f, -184.87f, 5.15344f, 1.39925f, },
	{ -139.196f, -181.959f, 5.15344f, 1.66235f },
	{ -126.49f, -187.267f, 5.15344f, 0.821977f },
	{ -129.651f, -183.149f, 5.15344f, 1.30892f },
	{ -133.909f, -180.081f, 5.15344f, 1.30892f },
	{ -127.956f, -179.24f, 5.15344f, 1.38354f, },
	{ -124.889f, -182.716f, 5.15344f, 0.539234f },
	{ -120.841f, -184.218f, 5.15344f, 0.539234f },
	{ -124.74f, -176.964f, 5.15344f, 1.28536f },
	{ -121.575f, -173.482f, 5.15344f, 1.37961f },
	{ -120.969f, -179.168f, 5.15344f, 0.0915573f },
	{ -116.581f, -181.668f, 5.15344f, 0.370374f },
	{ -118.178f, -175.807f, 5.15344f, 0.998692f },
	{ -113.994f, -174.668f, 5.15344f, 0.731657f },
	{ -113.402f, -180.036f, 5.15344f, 0.105393f },
	{ -110.95f, -173.717f, 5.15344f, 1.51126f },
	{ -109.159f, -177.192f, 5.15344f, 0.10932f },
	{ -105.659f, -173.393f, 5.15344f, 0.10932f },
	{ -104.187f, -177.629f, 5.15344f, 0.0189996f },
	{ -103.209f, -182.414f, 5.15344f, 0.0189996f },
	{ -100.927f, -173.656f, 5.15344f, 0.474531f },
	{ -100.239f, -178.169f, 5.15344f, 0.0857584f },
	{ -98.3092f, -182.19f, 5.15344f, 0.0857584f, },
	{ -96.5844f, -173.799f, 5.15344f, 0.352794f },
	{ -95.6767f, -178.641f, 5.15344f, 6.16867f },
	{ -93.5087f, -183.026f, 5.15344f, 6.1883f },
	{ -92.1973f, -175.457f, 5.15339f, 5.24975f },
	{ -92.1973f, -175.457f, 5.15339f, 5.24975f },
	{ -88.2974f - 177.41f, 5.15339f, 5.55605f },
	{ -90.6543f, -180.059f, 5.15339f, 5.55605f },
	{ -90.7933f, -184.847f, 5.15339f, 5.63852f },
	{ -86.0898f, -181.067f, 5.15339f, 5.93697f },
	{ -83.4694f, -177.367f, 5.15339f, 5.93697f },
	{ -85.4574f - 185.42f, 5.15339f, 5.7524f },
	{ -83.6811f, -188.552f, 5.15339f, 5.7524f },
	{ -81.7031f, -181.872f, 5.15339f, 0.0435462f },
	{ -77.7892f, -181.726f, 5.15339f, 5.91832f },
	{ -78.3222f, -187.637f, 5.15339f, 5.70627f },
	{ -74.0802f, -186.029f, 5.15339f, 5.91832f },
	{ -79.9036f, -191.617f, 5.15339f, 5.30571f },
	{ -73.917f, -191.124f, 5.15339f, 5.41174f },
	{ -68.7767f, -190.818f, 5.15339f, 5.56024f },
	{ -73.1456f, -196.314f, 5.15339f, 5.21539f },
	{ -75.8603f, -192.432f, 5.15339f, 6.08718f },
	{ -65.7269f, -195.123f, 5.15339f, 6.22462f },
	{ -69.4658f, -199.133f, 5.15339f, 5.19968f },
	{ -63.1817f, -200.844f, 5.15339f, 5.26251f },
	{ -61.5639f, -205.333f, 5.15339f, 0.0592449f },
	{ -58.7595f, -210.116f, 5.15339f, 6.18493f },
	{ -64.0941f, -211.393f, 5.15339f, 4.43334f },
	{ -63.7204f, -216.759f, 5.15339f, 4.49617f },
	{ -57.004f, -216.231f, 5.15339f, 5.09308f },
	{ -56.8338f, -221.237f, 5.15339f, 5.09308f },
	{ -63.5233f, -222.5f, 5.15339f, 4.87709f },
	{ -62.686f, -228.219f, 5.15342f, 5.15983f },
	{ -56.9591f, -227.926f, 5.15342f, 5.28583f },
	{ -69.8681f, -210.432f, 5.48133f, 0.00796175f },
	{ -66.3073f, -234.313f, 5.15342f, 5.56073f },
	{ -60.2881f, -240.613f, 5.15342f, 5.61178f },
	{ -68.7271f, -240.84f, 5.15342f, 4.52793f, },
	{ -63.1776f, -249.789f, 5.15342f, 4.74391f },
	{ -67.0089f, -253.58f, 5.15342f, 5.062f, },
	{ -73.575f, -250.239f, 5.15342f, 3.97029f },
	{ -72.6933f, -255.264f, 5.15342f, 5.34081f },
	{ -73.3079f, -261.094f, 5.15342f, 5.36044f },
	{ -79.0352f, -256.328f, 5.15342f, 4.68893f },
	{ -79.1966f, -263.206f, 5.15342f, 4.68893f },
	{ -85.5589f, -261.354f, 5.15342f, 4.53185f },
	{ -83.4055f, -266.208f, 5.15342f, 4.69285f },
	{ -90.0103f, -264.476f, 5.15342f, 4.41011f },
	{ -92.12f, -270.896f, 5.15342f, 4.37477f },
	{ -96.2131f, -264.443f, 5.38802f, 3.52261f },
	{ -96.1816f, -272.332f, 5.15341f, 3.81714f },
	{ -101.432f, -268.347f, 5.15341f, 3.54225f },
	{ -100.851f, -276.458f, 5.15341f, 3.91139f },
	{ -107.242f, -273.808f, 5.15341f, 3.7975f },
	{ -107.692f, -264.216f, 5.31491f, 2.84324f },
	{ -113.161f, -274.051f, 5.15344f, 4.04098f },
	{ -120.017f, -275.916f, 5.25548f, 3.42837f },
	{ -118.39f, -269.867f, 5.15343f, 2.47803f },
	{ -119.887f, -264.308f, 5.15343f, 2.69795f },
	{ -123.15f, -272.368f, 5.15343f, 3.53439f },
	{ -128.462f - 271.73f, 5.15343f, 3.81321f },
	{ -125.786f, -264.703f, 5.15343f, 2.33666f },
	{ -129.879f, -260.447f, 5.15343f, 2.33666f },
	{ -131.144f - 266.94f, 5.15343f, 3.58742f },
	{ -136.466f, -267.488f, 5.15343f, 3.59527f },
	{ -134.464f, -261.164f, 5.15343f, 2.34256f },
	{ -135.791f - 255.75f, 5.15343f, 2.57033f },
	{ -139.055f, -264.131f, 5.15343f, 3.28897f },
	{ -142.636f, -261.235f, 5.15343f, 3.25755f },
	{ -138.662f, -258.291f, 5.15343f, 1.89096f },
	{ -140.483f, -252.889f, 5.15343f, 1.90667f },
	{ -146.622f, -257.789f, 5.15343f, 2.50357f },
	{ -92.2886f - 258.54f, 5.15341f, 4.21967f },
	{ -97.4605f, -259.066f, 5.15341f, 4.16862f },
	{ -102.342f, -259.272f, 5.15341f, 4.16862f },
	{ -100.725f, -253.605f, 5.15341f, 5.26032f },
	{ -93.7281f - 252.87f, 5.15341f, 5.24854f },
	{ -106.397f, -253.738f, 5.15341f, 4.20003f },
	{ -109.014f, -258.39f, 5.15341f, 4.20003f, },
	{ -101.44f, -263.916f, 5.34436f, 4.25894f },
	{ -113.731f, - 261.808f,5.1534f, 4.18432f },
	{ -118.709f - 259.179f,	5.1534f, 4.09793f },
	{ -113.589f - 255.214f,	5.1534f, 5.39777f },
	{ -119.254f - 253.135f,	5.1534f, 3.87409f },
	{ -123.79f - 257.214f, 	5.1534f, 3.87409f },
	{ -130.499f, -243.604f, 5.15342f, 3.92122f },
	{ -134.505f, -246.835f, 5.15342f, 4.10186f },
	{ -134.505f, -246.835f, 5.15342f, 4.10186f },
	{ -138.959f, -242.836f, 5.15342f, 4.02725f },
	{ -134.54f, -238.514f, 5.15342f, 2.47216f },
	{ -142.299f, -237.999f, 5.15342f, 3.05465f },
	{ -137.955f, -235.623f, 5.15342f, 3.12926f },
	{ -132.454f, -232.603f, 5.02186f, 2.0729f },
	{ -137.703f, -231.424f, 5.15347f, 2.03756f },
	{ -143.24f, -232.8f, 5.15347f, 2.03756f },
	{ -144.79f, -227.347f, 5.15347f, 2.03756f },
	{ -139.745f, -226.958f, 5.15347f, 3.18817f },
	{ -136.186f, -222.206f, 5.15347f, 1.88048f },
	{ -140.733f, -220.928f, 5.15347f, 2.01998f },
	{ -144.656f, -222.819f, 5.15347f, 2.01998f },
	{ -144.128f, -218.522f, 5.15347f, 2.01998f },
	{ -143.282f, -213.087f, 5.15347f, 2.01998f },
	{ -138.776f, -217.099f, 5.15347f, 0.563068f },
	{ -134.332f - 218.633f,	5.1429f, 0.975402f },
	{ -135.676f, -212.948f, 5.15342f, 1.39227f },
	{ -139.855f, -210.979f, 5.15342f, 1.39227f },
	{ -141.264f - 207.83f, 5.15342f, 1.4983f },
	{ -137.941f, -204.957f, 5.15342f, 1.4983f },
	{ -133.197f, -208.939f, 5.15342f, 0.791437f },
	{ -133.967f, -203.609f, 5.15342f, 0.791437f },
	{ -128.923f, -204.798f, 5.15342f, 0.791437f },
	{ -134.937f, -198.682f, 5.15342f, 1.11738f },
	{ -132.288f - 195.47f, 5.15342f, 1.2666f },
	{ -130.143f, -199.671f, 5.15342f, 1.78889f },
	{ -127.591f - 193.63f, 5.15342f, 1.77711f },
	{ -125.438f, -200.781f, 5.15342f, 0.151338f },
	{ -113.02f, -194.848f, 5.15343f, 1.61218f },
	{ -113.816f, -191.219f, 5.15343f, 2.02844f },
	{ -117.085f, -187.352f, 5.15343f, 2.02844f },
	{ -112.291f, -186.559f, 5.15343f, 1.13309f },
	{ -109.219f, -191.406f, 5.15343f, 0.379104f },
	{ -107.867f, -195.789f, 5.15343f, 0.280929f },
	{ -106.889f, -186.569f, 5.15343f, 0.438009f },
	{ -103.873f, -189.342f, 5.15341f, 0.257367f },
	{ -101.087f, -185.669f, 5.15341f, 0.257367f },
	{ -97.6411f, -187.635f, 5.15341f, 0.257367f },
	{ -100.698f, -192.851f, 5.15341f, 5.63342f },
	{ -103.866f, -194.776f, 5.15341f, 5.42136f },
	{ -93.2132f, -188.621f, 5.1534f, 5.93187f },
	{ -95.9757f, -193.242f, 5.1534f, 5.71981f },
	{ -98.499f, -197.237f, 5.1534f, 0.155265f },
	{ -94.4599f, -198.303f, 5.1534f, 0.155265f },
	{ -91.656f, -193.968f, 5.1534f, 0.171546f },
	{ -87.3861f, -189.79f, 5.2284f, 6.16806f },
	{ -83.6853f, -194.054f, 5.15341f, 6.15235f },
	{ -88.068f, -197.891f, 5.15341f, 5.36695f },
	{ -91.8824f, -200.818f, 5.15341f, 5.36695f },
	{ -87.1429f, -204.179f, 5.15341f, 5.55938f },
	{ -81.5381f, -200.023f, 5.15341f, 5.84605f },
	{ -76.8685f, -197.888f, 5.60973f, 5.72824f },
	{ -77.343f, -204.021f, 5.15343f, 5.70468f },
	{ -83.0776f, -205.294f, 5.15343f, 4.18886f },
	{ -78.3549f, -207.545f, 5.15343f, 4.55799f },
	{ -73.7533f, -207.414f, 5.15343f, 5.08028f },
	{ -76.4261f, -211.866f, 5.15343f, 5.12348f },
	{ -80.9647f - 210.73f, 5.15343f, 4.31452f },
	{ -78.3341f, -215.545f, 5.15343f, 4.3263f },
	{ -71.6135f, -214.087f, 5.15343f, 4.93891f },
	{ -67.8177f, -216.284f, 5.51224f, 4.93891f },
	{ -71.4173f, -219.253f, 5.15343f, 4.95462f },
	{ -75.6709f, -219.724f, 5.15343f, 4.11424f },
	{ -69.1205f, -222.958f, 5.15343f, 4.44804f },
	{ -79.9343f, -220.044f, 5.15343f, 0.132272f },
	{ -80.7888f, -227.274f, 5.05935f, 5.87353f },
	{ -79.9894f, -231.626f, 5.15341f, 0.210808f },
	{ -77.7778f, -235.756f, 5.15341f, 0.167611f },
	{ -72.9098f, -236.689f, 5.15341f, 0.40323f },
	{ -73.9649f, -241.074f, 5.15341f, 5.48083f },
	{ -77.4022f, -240.346f, 5.15341f, 4.18099f },
	{ -81.6767f, -240.269f, 5.15341f, 4.18099f },
	{ -76.8543f, -244.969f, 5.15341f, 4.88f },
	{ -68.4949f, -248.555f, 5.15341f, 5.56722f },
	{ -60.8186f, -244.599f, 5.15341f, 5.65026f },
	{ -79.4829f, -249.24f, 	5.1534f, 4.39755f },
	{ -82.9686f, -244.878f,	5.1534f, 3.56053f },
	{ -87.0127f, -244.497f,	5.1534f, 3.70975f },
	{ -83.6863f, -249.266f,	5.1534f, 3.98464f },
	{ -83.3896f, -254.13f, 	5.1534f, 3.98464f },
	{ -87.8613f, -250.799f,	5.1534f, 3.67321f },
	{ -87.0392f, -256.87f, 5.15261f, 4.14444f },
	{ -91.4251f, -247.922f, 5.15261f, 3.40617f },
	{ -120.844f, -247.44f, 5.01989f, 3.10379f },
	{-123.66f, -243.933f, 4.88525f, 3.43366f },
	{ -120.116f - 238.127f,	3.6895f, 2.58936f },
	{ -124.892f, -240.016f, 4.50836f, 2.67575f },
	{ -126.747f, -236.431f, 4.40206f, 2.41657f },
	{ -129.415f, -239.461f, 5.04746f, 2.4205f },
	{ -123.62f, -233.806f, 3.69491f, 2.31839f },
	{ -129.663f, -230.872f, 4.43824f, 2.32232f },
	{ -125.572f, -227.348f, 3.63553f, 1.87464f },
	{ -133.149f, -226.813f, 4.98124f, 2.1299f },
	{ -129.15f, -222.369f, 4.22184f, 2.01994f },
	{ -124.37f, -220.966f, 3.64457f, 1.10495f },
	{ -130.304f, -216.526f, 4.70071f, 1.59975f },
	{ -124.145f, -216.348f, 3.67196f, 1.59975f },
	{ -129.892f, -212.225f, 4.88357f, 1.59975f },
	{ -126.175f - 209.493f,	4.6592f, 1.64295f },
	{ -121.643f, -213.362f, 3.59499f, 0.830064f },
	{ -123.964f, - 206.315f, 4.7417f, 0.951801f },
	{ -120.456f, -203.805f, 4.71822f, 0.998925f },
	{ -117.082f, -201.092f, 4.89176f, 0.912531f },
	{ -117.839f, -208.862f, 3.70131f, 6.14721f },
	{ -112.609f, -207.159f, 3.56817f, 0.111425f },
	{ -112.572f, -200.046f, 4.79051f, 0.504124f },
	{ -106.154f, -199.326f, 4.85289f, 0.539467f },
	{ -116.122f, -204.247f, 4.30976f, 4.56463f },
	{ -108.661f - 203.286f,	4.1728f, 4.86365f },
	{ -107.927f, -208.106f, 3.69275f, 4.86365f },
	{ -102.935f, -205.5f, 3.84508f, 5.44092f },
	{ -99.4686f, -201.011f, 4.80586f, 5.64512f },
	{ -96.1712f, -203.457f, 4.58672f, 5.64512f },
	{ -93.0684f, -205.653f, 4.59386f, 5.69225f },
	{ -98.2757f, -206.876f, 3.88629f, 4.93041f },
	{ -95.8318f, -210.518f, 3.61738f, 5.54695f },
	{ -88.946f, -208.138f, 4.75188f, 5.57051f },
	{ -92.4191f, -211.517f, 3.88854f, 5.48019f },
	{ -86.8618f - 211.561f,	4.6847f, 5.70795f },
	{ -84.3222f, -215.163f, 4.81266f, 5.70403f },
	{ -90.5256f - 214.179f,	3.8918f, 4.1725f },
	{ -87.67f, -220.504f, 3.93268f, 4.32958f },
	{ -84.72f, -225.632f, 4.40559f, 4.68301f },
	{ -89.8081f, -225.242f, 3.50222f, 4.63588f },
	{ -87.0151f, -229.701f, 4.11413f, 5.3506f },
	{ -83.7154f, -233.914f, 4.91805f, 5.39772f },
	{ -90.8014f, -234.493f, 3.76919f, 4.27853f },
	{ -85.8012f, -238.257f, 4.88224f, 4.34921f },
	{ -93.6913f - 237.79f, 3.77396f, 3.98007f },
	{ -89.6829f, -239.115f, 4.46614f, 3.01403f },
	{ -93.6573f, -244.096f, 4.58384f, 3.06116f },
	{ -97.5403f, -240.521f, 3.70674f, 3.28107f },
	{ -95.6944f, -247.486f, 4.97034f, 4.00364f },
	{ -101.834f, -247.532f, 4.52645f, 4.07825f },
	{ -102.292f, -241.915f, 3.56111f, 3.16719f },
	{ -106.309f, -242.704f, 3.61903f, 3.25358f },
	{ -106.341f, -250.223f, 4.95966f, 3.72482f },
	{ -110.772f, -248.066f, 4.53467f, 3.77194f },
	{ -114.965f, -247.605f, 4.70292f, 3.77194f },
	{ -111.179f, -252.176f, 5.14339f, 4.49058f },
	{ -111.934f, -242.515f, 3.66624f, 2.88052f },
	{ -106.693f - 245.41f, 4.09769f, 4.20784f },
	{ -97.6727f, -242.954f, 4.08769f, 5.39379f },
	{ -117.52f, -241.105f, 3.77861f, 4.10966f },
	{ -118.44f, -243.507f, 4.21373f, 4.60839f },
	{ -97.9411f, -236.06f, 3.50114f, 0.174814f },
	{ -96.5536f, -231.252f, 3.50114f, 0.32404f },
	{ -92.1938f, -228.664f, 3.66247f, 0.795279f },
	{ -95.5022f, -225.722f, 3.50113f, 1.87127f },
	{ -94.2792f, -221.672f, 3.50113f, 1.8752f },
	{ -97.8423f, -218.76f, 3.50113f, 2.13438f, },
	{ -94.0306f, -214.955f, 3.69274f, 2.13438f },
	{ -91.588f,  -219.0f, 3.69274f, 3.68554f },
	{ -100.097f, -214.054f, 3.50114f, 3.79843f },
	{ -104.532f, -210.606f, 3.50114f, 3.78665f },
	{ -106.409f, -213.64f, 3.50114f, 3.79843f, },
	{ -111.362f, -213.198f, 3.50114f, 3.90054f },
	{ -116.496f, -213.367f, 3.50114f, 4.14736f },
	{ -115.074f, -219.501f, 3.50114f, 4.81888f },
	{ -120.461f, -219.141f, 3.50114f, 5.61998f },
	{ -120.503f, -224.981f, 3.50114f, 5.63198f },
	{ -116.206f - 226.92f, 3.50114f, 5.63198f },
	{ -119.7f, -231.462f, 3.50114f, 5.62748f },
	{ -115.228f, -236.135f, 3.50111f, 0.602861f },
	{ -113.642f, -230.904f, 3.50111f, 0.661766f },
	{ -108.693f, -234.609f, 3.50111f, 0.756014f },
	{ -110.991f, -239.145f, 3.50111f, 5.8022f },
	{ -105.222f, -237.524f, 3.50111f, 5.87288f },
	{ -103.535f, -232.353f, 3.51732f, 0.0636463f },
	{ -100.268f, -226.869f, 3.50111f, 0.0636463f },
	{ -101.307f, -221.497f, 3.50111f, 0.601644f },
	{ -106.092f, -218.464f, 3.50111f, 1.44987f },
	{ -110.92f, -220.551f, 3.50111f, 2.50231f },
	{ -110.751f, -226.796f, 3.50111f, 3.09136f },
	{ -106.161f, -229.324f, 3.50111f, 5.07056f },
	{ -112.501f, -224.067f, 3.50112f, 0.436709f },
	{ -111.224f, -216.176f, 3.50111f, 1.74047f },
	{ -102.087f, -215.363f, 3.011f,  0.4278f },
	{-129.511f, -269.437f,5.15344f,2.84325f},
	{-111.871f, -268.674f,5.15344f,2.43877f},
	{-121.323f, -259.993f,5.15387f,3.48335f},
	{-91.5518f, -254.537f,5.15341f,0.852261f},
	{-96.4506f, -250.483f,5.15341f,2.11283f},
	{-76.8548f, -258.807f,5.15343f,3.50691f},
	{-65.9352f, -243.966f,5.15343f,4.96774f},
	{-62.9297f, -237.812f,5.15343f,4.82245f},
	{-59.3665f, -232.778f,5.15343f,4.74391f},
	{-73.2151f, -201.359f,5.34549f,3.80929f},
	{-68.1341f, -204.262f,5.1534f,5.80812f},
	{-86.8366f, -184.321f,5.15343f,0.125772f},
	{-109.699f, -182.046f,5.15342f,0.41637f},
	{-141.868f, -200.318f,5.15344f,0.993638f},
	{-159.439f, -236.24f,	5.22117f,2.25813f},
	{-140.038f, -248.696f,5.45201f,0.110065f},
	{-135.137f, -254.433f,5.40678f,2.43877f},
	{-124.905f, -256.78f,	5.15362f,1.91648f},
	{-114.959f, -254.653f,5.15343f,1.38634f}
};

class boss_bd_nefarian : public CreatureScript
{
public:
    boss_bd_nefarian() : CreatureScript("boss_bd_nefarian") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_bd_nefarianAI (creature);
    }

    struct boss_bd_nefarianAI : public BossAI
    {
		boss_bd_nefarianAI(Creature* creature) : BossAI(creature, DATA_NEFARIAN), summonsfire(me)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        Phases phase;
        uint32 m_uiOnyxiaCheckTimer;
        uint32 m_uiDistanceCheckTimer;
        uint32 m_uiChromaticCheckTimer;
		SummonList summonsfire; 
		bool onyxiaAlive, electrocute, said, secondPhase, finalPhase;
		bool electrocute9;
		bool electrocute8;
		bool electrocute7;
		bool electrocute6;
		bool electrocute5;
		bool electrocute4;
		bool electrocute3;
		bool electrocute2;
		bool electrocute1;

        void Reset()
        {
            events.Reset();
            phase = PHASE_NULL;
            onyxiaAlive = true;
            said = false;
            electrocute = false;
            secondPhase = false;
			summonsfire.DespawnAll();
            finalPhase = false;
			electrocute9 = false;
			electrocute8 = false;
			electrocute7 = false;
			electrocute6 = false;
			electrocute5 = false;
			electrocute4 = false;
			electrocute3 = false;
			electrocute2 = false;
			electrocute1 = false;
            if (instance)
                instance->SetBossState(DATA_NEFARIAN, NOT_STARTED);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);				
			me->SetFloatValue(UNIT_FIELD_BOUNDING_RADIUS, 40.0f);
			me->SetFloatValue(UNIT_FIELD_COMBAT_REACH, 40.0f);
			if (Creature* onyxia = me->FindNearestCreature(NPC_ONYXIA, 150.0f, true)){
				summonsfire.Summon(onyxia);
			}
				
				
			/*me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
			me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);	*/		
            _Reset();			
        }

		void SummonedCreatureDespawn(Creature* summon)
		{
			summonsfire.Despawn(summon);
		}

        void IsSummonedBy(Unit* summoner)
        {
            DoZoneInCombat(me, 200.0f);
            if(Creature* Onyxia = me->FindNearestCreature(NPC_ONYXIA, 200.0f, true))
                Onyxia->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void EnterEvadeMode()
        {
            Reset();

            me->DespawnOrUnsummon(1000);
            me->SummonCreature(NPC_NEFARIAN_INTRO, -167.093f, -224.479f, 40.399f, 6.278f, TEMPSUMMON_MANUAL_DESPAWN);

            if (instance)
            {
                instance->SetBossState(DATA_NEFARIAN, FAIL);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            _EnterEvadeMode();
        }

        void EnterCombat(Unit* /*pWho*/)
        {
            EnterPhaseIntro();
            
            if (instance)
            {
                instance->SetBossState(DATA_NEFARIAN, IN_PROGRESS);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add
            }
			
            _EnterCombat();
        }

        void JustDied(Unit* /*killer*/)
        {
            me->RemoveAllAuras();		
			summonsfire.DespawnAll();
            if (instance)
            {
                instance->SetBossState(DATA_NEFARIAN, DONE);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
				instance->DoModifyPlayerCurrenciesIfLevel(395, 7500, 85);
            }

            Talk(SAY_DEATH);

            _JustDied();
        }

        void KilledUnit(Unit* /*victim*/) 
        {
            Talk(SAY_KILL-urand(0,1));
			if (!me->FindNearestPlayer(200.0f, true))
				EnterEvadeMode();
        }

        void DamageTaken(Unit* who, uint32& damage)
        {			
			if (me->HealthBelowPctDamaged(90, damage) && !electrocute9){
				electrocute9 = true;
				electrocute = true;
			}
			if (me->HealthBelowPctDamaged(80, damage) && !electrocute8){
				electrocute8 = true;
				electrocute = true;
			}
			if (me->HealthBelowPctDamaged(70, damage) && !electrocute7){
				electrocute7 = true;
				electrocute = true;
			}
			if (me->HealthBelowPctDamaged(60, damage) && !electrocute6){
				electrocute6 = true;
				electrocute = true;
			}
			if (me->HealthBelowPctDamaged(50, damage) && !electrocute5){
				electrocute5 = true;
				electrocute = true;
			}
			if (me->HealthBelowPctDamaged(40, damage) && !electrocute4){
				electrocute4 = true;
				electrocute = true;
			}
			if (me->HealthBelowPctDamaged(30, damage) && !electrocute3){
				electrocute3 = true;
				electrocute = true;
			}
			if (me->HealthBelowPctDamaged(20, damage) && !electrocute2){
				electrocute2 = true;
				electrocute = true;
			}
			if (me->HealthBelowPctDamaged(10, damage) && !electrocute1){
				electrocute1 = true;
				electrocute = true;
			}
				
			if (electrocute)
            {	
				electrocute = false;
                events.ScheduleEvent(EVENT_ELECTROCUTE, 100);
            }
        }

        void EnterPhaseIntro()
        {
            phase = PHASE_INTRO;
            events.SetPhase(PHASE_INTRO);
            initIntroEvents();            
        }

        void EnterPhaseGround()
        {
            phase = PHASE_GROUND;
            events.SetPhase(PHASE_GROUND);
            initEvents(true);
            m_uiOnyxiaCheckTimer = 5000;
            m_uiDistanceCheckTimer = 5000;
        }

        void EnterPhaseAir()
        {
            phase = PHASE_FLIGHT;
            events.SetPhase(PHASE_FLIGHT);
            initEvents(false);
            m_uiChromaticCheckTimer = 2000;
        }

        void EnterPhaseFinal()
        {
            phase = PHASE_FINAL;
            events.SetPhase(PHASE_FINAL);
            initFinalEvents();
        }

        void initEvents(bool onGround = true)
        {
            events.Reset();

            if(onGround)
            {
                events.ScheduleEvent(EVENT_SHADOWFLAME_BREATH, 5000, PHASE_GROUND);
                events.ScheduleEvent(EVENT_SHADOW_COWARDICE, 20000, PHASE_GROUND);
            }else
            {    
                events.ScheduleEvent(EVENT_SHADOWFLAME_BARRAGE, 4000, PHASE_FLIGHT);
                events.ScheduleEvent(EVENT_SUMMON_CHROMATIC, 500, PHASE_FLIGHT);
            }
        }

        void initIntroEvents()
        {
            events.Reset();
			me->SetReactState(REACT_PASSIVE);
            events.ScheduleEvent(EVENT_INTRO, 100);
            events.ScheduleEvent(EVENT_INTRO2, 9900);
            events.ScheduleEvent(EVENT_MOVE, 34000);
        }

        void initFinalEvents()
        {
            events.Reset();

            events.ScheduleEvent(EVENT_TAIL_LASH, 4000, PHASE_FINAL);
            events.ScheduleEvent(EVENT_SHADOWFLAME_BREATH, 5000, PHASE_FINAL);
            events.ScheduleEvent(EVENT_SHADOWBLAZE, 9000, PHASE_FINAL);
            events.ScheduleEvent(EVENT_REVIVE_SKELETONS, 1000, PHASE_FINAL);
        }

        void JustSummoned(Creature* summon)
        {
            summon->AI()->DoZoneInCombat();
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (Creature* Onyxia = me->FindNearestCreature(NPC_ONYXIA, 150.0f, true))
                if (Onyxia && !Onyxia->isInCombat() && said == false)
                {
                    Talk(SAY_AVOID_WIPE);
                    said = true;
                }

            if (phase == PHASE_GROUND && m_uiDistanceCheckTimer <= diff)
            {
                if (me->FindNearestCreature(NPC_ONYXIA, 40.0f, true) && onyxiaAlive && !me->HasAura(SPELL_CHILDREN_OF_DEATHWING_ONY))
                    me->AddAura(SPELL_CHILDREN_OF_DEATHWING_ONY, me);
                else if (!me->FindNearestCreature(NPC_ONYXIA, 50.0f, true) && onyxiaAlive)
                    if(me->HasAura(SPELL_CHILDREN_OF_DEATHWING_ONY))
                       me->RemoveAura(SPELL_CHILDREN_OF_DEATHWING_ONY);

                m_uiDistanceCheckTimer = 5000;
            }
            else m_uiDistanceCheckTimer -= diff;

            if (phase == PHASE_GROUND && m_uiOnyxiaCheckTimer <= diff && !secondPhase)
            {
                if (me->FindNearestCreature(NPC_ONYXIA, 150.0f, true))
                    onyxiaAlive = true;
                else
                {
                    onyxiaAlive = false;
                    Talk(SAY_AIR_PHASE);
                    if(me->HasAura(SPELL_CHILDREN_OF_DEATHWING_ONY))
                       me->RemoveAura(SPELL_CHILDREN_OF_DEATHWING_ONY);
                    events.ScheduleEvent(EVENT_LIFTOFF, 5000, PHASE_GROUND);
                    secondPhase = true;
                }

                m_uiOnyxiaCheckTimer = 5000;
            }
            else m_uiOnyxiaCheckTimer -= diff;

            if (phase == PHASE_FLIGHT && m_uiChromaticCheckTimer <= diff && !finalPhase)
            {
				if (!me->FindNearestCreature(NPC_CHROMATIC_PROTO, 150.0f, true)){
					events.ScheduleEvent(EVENT_LAND, 2000, PHASE_FLIGHT);
					finalPhase = true;
				}  

                m_uiChromaticCheckTimer = 2000;
            }
            else m_uiChromaticCheckTimer -= diff;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_ELECTROCUTE:				
                        DoCast(me, SPELL_ELECTROCUTE);
                        break;

                    case EVENT_INTRO:						
                        me->HandleEmote(EMOTE_ONESHOT_LIFTOFF);
                        me->SetDisableGravity(true);
                        me->SendMovementFlagUpdate();
						me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                        me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
                        me->GetMotionMaster()->MovePoint(1, -126.518f, -233.342f, 36.358f); // Position on top of raid.
                        break;

                    case EVENT_INTRO2:
                        Talk(SAY_AGGRO);
						me->SetReactState(REACT_AGGRESSIVE);
                        events.ScheduleEvent(EVENT_HAIL_OF_BONES, 100);
                        break;

                    case EVENT_HAIL_OF_BONES:
                        DoCast(me, SPELL_HAIL_OF_BONES);
                        break;

                    case EVENT_MOVE:
                        me->GetMotionMaster()->MovePoint(1, -100.123f, -221.522f, 7.156f); // Move down.
                        events.ScheduleEvent(EVENT_LANDING, 8000);                        
                        break;
            
                    case EVENT_LANDING:
                        me->HandleEmote(EMOTE_ONESHOT_LAND);
						me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
						me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);	
                        me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
                        me->SetDisableGravity(false);
                        me->SendMovementFlagUpdate();
                        EnterPhaseGround();
                        me->GetMotionMaster()->MoveChase(me->getVictim());
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        break;

                    case EVENT_SHADOWFLAME_BREATH:
                        Talk(SAY_SHADOWFLAME);
                        DoCastVictim(SPELL_SHADOWFLAME_BREATH);   
                        events.ScheduleEvent(EVENT_SHADOWFLAME_BREATH, urand(10000, 12000));
                        break;
                         
                    case EVENT_SHADOW_COWARDICE:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            DoCast(target, SPELL_SHADOW_COWARDICE);                 
                        events.ScheduleEvent(EVENT_SHADOW_COWARDICE, urand(9000, 10000));
                        break;

                    case EVENT_LIFTOFF:

                        Talk(SAY_AIR_PHASE_2);
						for (auto itr:firefloor){
							Creature* fire = me->SummonCreature(100090, itr, TEMPSUMMON_MANUAL_DESPAWN);
							summonsfire.Summon(fire);
						}
						me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
						me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        me->HandleEmote(EMOTE_ONESHOT_LIFTOFF);
                        me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
                        me->SetDisableGravity(true);
                        me->SendMovementFlagUpdate();
                        events.ScheduleEvent(EVENT_FLIGHT, 500);
                        events.ScheduleEvent(EVENT_AIR, 1500);
                        break;

                    case EVENT_FLIGHT:
                        me->SetReactState(REACT_PASSIVE);
                        me->AttackStop();
                        me->GetMotionMaster()->MovePoint(1, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 30.0f);
                        break;

                    case EVENT_AIR:
                        EnterPhaseAir();
                        break;

                    case EVENT_SUMMON_CHROMATIC:
						for (Position pos : npc_chromatic){
							summonsfire.Summon(me->SummonCreature(NPC_CHROMATIC_PROTO, pos, TEMPSUMMON_MANUAL_DESPAWN));
						}
                        break;

                    case EVENT_SHADOWFLAME_BARRAGE:
                        if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true))
                            DoCast(target, SPELL_SHADOWFLAME_BARRAGE);
                        events.ScheduleEvent(EVENT_SHADOWFLAME_BARRAGE, urand(8000, 11000));
                        break;

                    case EVENT_LAND:						
						me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
						me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        me->HandleEmote(EMOTE_ONESHOT_LAND);
                        me->SetDisableGravity(false);
                        me->SendMovementFlagUpdate();
                        me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
                        events.ScheduleEvent(EVENT_RETURN, 1000);
                        events.ScheduleEvent(EVENT_GROUND, 1500);
                        break;

                    case EVENT_RETURN:
                        me->SetReactState(REACT_PASSIVE);
                        me->AttackStop();
                        me->GetMotionMaster()->MovePoint(1, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() - 30.0f);
                        break;
            
                    case EVENT_GROUND:
                        EnterPhaseFinal();
                        me->SetReactState(REACT_AGGRESSIVE);
                        AttackStart(me->getVictim());
                        me->GetMotionMaster()->MoveChase(me->getVictim());
						summonsfire.DespawnAll();
                        Talk(SAY_FINAL_PHASE);
                        break;

                    case EVENT_TAIL_LASH:
                        DoCast(me, SPELL_TAIL_LASH);
                        events.ScheduleEvent(EVENT_TAIL_LASH, urand(8000, 11000));
                        break;

                    case EVENT_SHADOWBLAZE:
                        if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true))
                            DoCast(target, SPELL_SHADOWBLAZE_SPARK);
						events.ScheduleEvent(EVENT_SHADOWBLAZE, urand(18000, 21000));
                        break;

                    case EVENT_REVIVE_SKELETONS:
                    {
                        std::list<Creature*> creatures;
                        GetCreatureListWithEntryInGrid(creatures, me, 41918, 200.0f);

                        if (!creatures.empty())
                        for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        {
                            DoCast((*iter), SPELL_ANIMATE_BONES, true);
                            (*iter)->SetReactState(REACT_AGGRESSIVE);
                            (*iter)->RemoveAura(SPELL_DIE_VISUAL);
                        }
                    }
                        break;
                }
            }

            if (phase == PHASE_GROUND || phase == PHASE_FINAL)
                DoMeleeAttackIfReady();
        }
    private:
    };
};

class boss_bd_onyxia : public CreatureScript
{
public:
    boss_bd_onyxia() : CreatureScript("boss_bd_onyxia") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_bd_onyxiaAI (creature);
    }

    struct boss_bd_onyxiaAI : public ScriptedAI
    {
        boss_bd_onyxiaAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
			me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
			me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
			me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_STUN, true);
			me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FEAR, true);
			me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_ROOT, true);
			me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FREEZE, true);
			me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_POLYMORPH, true);
			me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_HORROR, true);
			me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SAPPED, true);
			me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_CHARM, true);
			me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_DISORIENTED, true);
			me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_CONFUSE, true);
        }

        InstanceScript* instance;
        EventMap events;
        uint32 m_uiDistancesCheckTimer;
        uint32 m_uiPowerTimer;

        void Reset()
        {
            events.Reset();           
            me->SetReactState(REACT_DEFENSIVE);
			me->SetFloatValue(UNIT_FIELD_BOUNDING_RADIUS, 40.0f);
			me->SetFloatValue(UNIT_FIELD_COMBAT_REACH, 40.0f);
			me->SetFloatValue(UNIT_FIELD_MINDAMAGE, 15000.0f);
			me->SetFloatValue(UNIT_FIELD_MAXDAMAGE, 18000.0f);
			me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
			me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }

		void JustDied(Unit* who)
		{
			removeLightBar();				
			instance->SetBossState(DATA_ONYXIA, DONE);
		}

        void EnterEvadeMode()
        {
            me->DespawnOrUnsummon(100);
        }

		void EnterCombat(Unit* /*pWho*/){
			me->SetReactState(REACT_AGGRESSIVE);
			addLightBar();
			events.ScheduleEvent(EVENT_LIGHTNING_DISCHARGE, urand(22000, 25000));
			events.ScheduleEvent(EVENT_SF_BREATH, urand(13000, 17000));
			events.ScheduleEvent(EVENT_TAL_LASH, urand(8000, 11000));
			events.ScheduleEvent(EVENT_INCREASE_BAR, 1000);
			DoZoneInCombat();
			instance->SetBossState(DATA_ONYXIA, IN_PROGRESS);
		}

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (m_uiDistancesCheckTimer <= diff)
            {
                if (me->FindNearestCreature(NPC_NEFARIAN, 50.0f, true) && !me->HasAura(SPELL_CHILDREN_OF_DEATHWING_ONY))
                    me->AddAura(SPELL_CHILDREN_OF_DEATHWING_NEF, me);
				else if (!me->FindNearestCreature(NPC_NEFARIAN, 50.0f, true))
                    if(me->HasAura(SPELL_CHILDREN_OF_DEATHWING_NEF))
                       me->RemoveAura(SPELL_CHILDREN_OF_DEATHWING_NEF);

                m_uiDistancesCheckTimer = 5000;
            }
            
			else m_uiDistancesCheckTimer -= diff;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SF_BREATH:
						DoCastVictim(SPELL_SHADOWFLAME_BREATH);
						events.ScheduleEvent(EVENT_SF_BREATH, urand(13000, 17000));
						break;                       

                    case EVENT_LIGHTNING_DISCHARGE:
						DoCast(me, SPELL_LIGHTNING_DISCHARGE);
						events.ScheduleEvent(EVENT_LIGHTNING_DISCHARGE, urand(22000, 25000));
						break;

                    case EVENT_TAL_LASH:
						DoCast(me, SPELL_TAIL_LASH);
						events.ScheduleEvent(EVENT_TAL_LASH, urand(8000, 11000));
						break;
					case EVENT_INCREASE_BAR:
						DoCast(me, SPELL_INCREASE_BAR);
						events.ScheduleEvent(EVENT_INCREASE_BAR, 1000);
						break;

                }
            }

            DoMeleeAttackIfReady();
        }

	private:
		void addLightBar() {
			me->AddAura(SPELL_ONYXIA_DISCHARGE_BAR, me);			
		}

		void removeLightBar() {
			me->RemoveAura(SPELL_ONYXIA_DISCHARGE_BAR);			
		}
    };
};

class npc_nefarian_intro : public CreatureScript // 41379
{
public:
    npc_nefarian_intro() : CreatureScript("npc_nefarian_intro") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_nefarian_introAI (creature);
    }

    struct npc_nefarian_introAI : public ScriptedAI
    {
        npc_nefarian_introAI(Creature* creature) : ScriptedAI(creature) { instance = creature->GetInstanceScript(); }

        InstanceScript* instance;
        EventMap events;
        bool introDone;

        void Reset()
        {
            if (GameObject* elevator = me->FindNearestGameObject(207834, 200.0f))
                elevator->SetGoState(GO_STATE_READY);
           
            events.Reset();            
			findPlayers = false;
			not_prepare = false;
			me->SetReactState(REACT_PASSIVE);
        }

        void EnterCombat(Unit* /*who*/)
        {			
                   
        }

        void JustSummoned(Creature* summon)
        {
			if (summon->GetEntry() == NPC_NEFARIAN)
            {
                  summon->AI()->DoZoneInCombat();
            }
        }

        void UpdateAI(const uint32 diff)
        {
            //if(instance->GetBossState(BOSS_CHIMAERON) == DONE)
            //    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_INTRO_1:
						me->MonsterSay("Ha ha ha ha ha! The heroes have made it to the glorious finale! I take it you are in good spirits? Prepared for the final battle? Then gaze now upon my ultimate creation! RISE, SISTER!", 0, 0);
                        Talk(SAY_INTRO_1);//Este texto hay que ponerlo en la BD						
							
                        events.ScheduleEvent(EVENT_SUMMON_ONYXIA, 14000);
                        events.ScheduleEvent(EVENT_INTRO_2, 15000);
                        break;

                    case EVENT_SUMMON_ONYXIA:
                        onyxia = me->SummonCreature(NPC_ONYXIA, -104.713f, -225.264f, 7.156f, 3.122f, TEMPSUMMON_MANUAL_DESPAWN);	
						onyxia->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
						onyxia->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);						

						switch (instance->instance->GetDifficulty()){
							case RAID_DIFFICULTY_10MAN_NORMAL:
								onyxia->SetMaxHealth(6600000);
								onyxia->SetHealth(6600000);
								break;
							case RAID_DIFFICULTY_25MAN_NORMAL:
								onyxia->SetMaxHealth(24000000);
								onyxia->SetHealth(24000000);
								break;
						}
						
                        break;

                    case EVENT_INTRO_2:
                        Talk(SAY_INTRO_2);
						me->MonsterSay("Behold, the Broodmother... Onyxia... REBORN. Perhaps my finest work.", 0, 0);
                        events.ScheduleEvent(EVENT_INTRO_3, 10000);
                        break;

                    case EVENT_INTRO_3:
                        Talk(SAY_INTRO_3);
						me->MonsterSay("My dearest sibling... do you hunger? THEN FEAST UPON OUR ENEMIES!", 0, 0);
                        introDone = true;
                        events.ScheduleEvent(EVENT_SUMMON_NEFARIAN, 7500);
                        me->DespawnOrUnsummon(8000);
                        break;

					case EVENT_SUMMON_NEFARIAN:{
						Creature* nefariand = me->SummonCreature(NPC_NEFARIAN, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1200000);
						switch (instance->instance->GetDifficulty()){
						case RAID_DIFFICULTY_10MAN_NORMAL:
							nefariand->SetMaxHealth(28516144);
							nefariand->SetHealth(28516144);
							break;
						case RAID_DIFFICULTY_25MAN_NORMAL:
							nefariand->SetMaxHealth(99634720);
							nefariand->SetHealth(99634720);
							break;
						}
						nefariand->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
						nefariand->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
						break;
					}
					case EVENT_NOT_PREPARE:
						me->MonsterSay("Ha ha ha ha! Poor mortals, at this moment you are not prepare to face me. First defeat my servants!", 0, 0);
						events.ScheduleEvent(EVENT_NOT_PREPARE, 10000);
						break;
						
                }
            }

			if (!findPlayers && me->SelectNearestPlayer(5.0f)){
				if (instance->CheckRequiredBosses(DATA_NEFARIAN)){
					findPlayers = true;
					events.ScheduleEvent(EVENT_INTRO_1, 2000);
				}
				else if (!not_prepare){
					events.ScheduleEvent(EVENT_NOT_PREPARE, 100);
					not_prepare = true;
				}
			}
			else{
				not_prepare = false;
				events.CancelEvent(EVENT_NOT_PREPARE);
			}
        }	

        void DamageTaken(Unit* /*who*/, uint32& damage)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            me->SetReactState(REACT_PASSIVE);
            me->AttackStop();
        }

		private:
			bool findPlayers;
			Creature* onyxia;
			bool not_prepare;

    };
};

class npc_animated_bone_warrior : public CreatureScript
{
public:
    npc_animated_bone_warrior() : CreatureScript("npc_animated_bone_warrior") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_animated_bone_warriorAI (creature);
    }

    struct npc_animated_bone_warriorAI : public ScriptedAI
    {
        npc_animated_bone_warriorAI(Creature* creature) : ScriptedAI(creature) 
        {
            //ASSERT(creature->GetVehicleKit()); // get and set power type.
            
        }

		void Reset(){
			me->SetReactState(REACT_AGGRESSIVE);	
			me->SetFloatValue(UNIT_FIELD_BOUNDING_RADIUS, 15.0f);
			me->SetFloatValue(UNIT_FIELD_COMBAT_REACH, 15.0f);	
			me->SetPower(POWER_ENERGY, 100);
			me->SetMaxPower(POWER_ENERGY, 100);			
		}

		uint16 power;
		void IsSummonedBy(Unit* summoner) override
		{
			Reset();			
		}

        void EnterCombat(Unit* who)
        {           
			events.ScheduleEvent(1, urand(4000, 9000));
			events.ScheduleEvent(2, 2000);
			power = 100;
            me->AddAura(SPELL_NO_REGEN, me);
            me->AddAura(SPELL_NO_REGEN2, me);
            DoCast(me, SPELL_ANIMATE_BONES);
            DoCast(me, SPELL_EMPOWER);
			me->GetMotionMaster()->MoveFollow(who, 0.0f, 0.0f);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
				return;

			if (Player* target = me->SelectNearestPlayer(50.0f)){				
				me->AI()->AttackStart(target);
				EnterCombat(target);				
			}
			
			me->SetReactState(REACT_AGGRESSIVE);

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent()){
				switch (eventId)
				{
				case 1:
					DoCastVictim(SPELL_HURL_BONE);					
					events.ScheduleEvent(1, urand(8000, 14000));
					break;
				case 2:
					if (power == 0)
					{
						me->RemoveAura(SPELL_ANIMATE_BONES);
						DoCast(me, SPELL_DIE_VISUAL);
						me->SetPower(POWER_ENERGY, 0);
					}
					else{
						power -= 5;
						events.ScheduleEvent(2, 2000);
					}
					break;
				}
				
			}

            if(me->HasAura(SPELL_ANIMATE_BONES))
				DoMeleeAttackIfReady();
			
        }

        void JustDied(Unit* /*killer*/)
        {
            me->DespawnOrUnsummon(100);
        }
    };
};

class npc_chromatic_prototype : public CreatureScript
{
public:
    npc_chromatic_prototype() : CreatureScript("npc_chromatic_prototype") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_chromatic_prototypeAI (creature);
    }

    struct npc_chromatic_prototypeAI : public ScriptedAI
    {
        npc_chromatic_prototypeAI(Creature* creature) : ScriptedAI(creature) { }

        void EnterCombat(Unit* /*who*/)
        {
            me->AddAura(SPELL_NOVA, me);
            me->SetReactState(REACT_PASSIVE);           
        }

        void UpdateAI(const uint32 diff) { }

        void JustDied(Unit* /*killer*/) { }
    };
};

class npc_shadowflame_flashfire : public CreatureScript
{
public:
    npc_shadowflame_flashfire() : CreatureScript("npc_shadowflame_flashfire") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_shadowflame_flashfireAI (creature);
    }

    struct npc_shadowflame_flashfireAI : public ScriptedAI
    {
        npc_shadowflame_flashfireAI(Creature* creature) : ScriptedAI(creature)
        {
            creature->SetReactState(REACT_PASSIVE);			
			timerMove = 1000;
			timerDespawn = 30000;
			timerSpawn = 1500;
        }

        uint32 timerMove;
        uint32 timerDespawn;
        uint32 timerSpawn;
		

		void Reset(){
			events.Reset();
			events.ScheduleEvent(3, 1500);
			events.ScheduleEvent(1, 20000);
		}

		void IsSummonedBy(Unit* summoner) override
		{
			Reset();			
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
			me->SetReactState(REACT_PASSIVE);					
		}

		void UpdateAI(const uint32 diff)
        {		
			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent()){
				switch (eventId)
				{
					case 1:
						me->DespawnOrUnsummon();
						break;
					case 3:
						me->SummonCreature(MOB_SHADOWBLAZE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 4000);
						uint32 pos = irand(0, 300);
						me->GetMotionMaster()->MovePoint(1, firefloor[pos]);
						events.ScheduleEvent(3, 1500);
						break;
				}
			}           
        }
    };
};

class npc_shadowblaze : public CreatureScript
{
public:
    npc_shadowblaze() : CreatureScript("npc_shadowblaze") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_shadowblazeAI (creature);
    }

    struct npc_shadowblazeAI : public ScriptedAI
    {
        npc_shadowblazeAI(Creature* creature) : ScriptedAI(creature) { }


        void IsSummonedBy(Unit* summoner) override
        {
			events.ScheduleEvent(1, 100);
			events.ScheduleEvent(2, 6100);
			DoCast(me, SPELL_FIREBRUSH_AURA);           
        }

        void UpdateAI(const uint32 diff)
        {
			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent()){
				switch (eventId)
				{
					case 1:
						if (Unit* skeleton = me->FindNearestCreature(NPC_ANIM_BONE_WARR, 4.0f, true))
							skeleton->CastSpell(skeleton, SPELL_ANIMATE_BONES, true);
						events.ScheduleEvent(1, 980);						
						DoCast(me, SPELL_FIREBRUSH_AURA);
						break;
					case 2:
						me->DespawnOrUnsummon();
						break;
				}
			}
        }

        void JustDied(Unit* /*killer*/) { }
    };
};

class npc_firefloor : public CreatureScript
{
public:
	npc_firefloor() : CreatureScript("npc_firefloor") { }

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_firefloorAI(pCreature);
	}

	struct npc_firefloorAI : public ScriptedAI
	{
		npc_firefloorAI(Creature* pCreature) : ScriptedAI(pCreature)
		{
			pInstance = pCreature->GetInstanceScript();
		}

		InstanceScript* pInstance;
		uint32 uiFlameTimer;


		void Reset()
		{
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			me->SetReactState(REACT_PASSIVE);
			DoCast(me, 66318);
			events.ScheduleEvent(1, 5000);
		}

		void JustDied(Unit* /*killer*/)
		{
			me->DespawnOrUnsummon();
		}

		void IsSummonedBy(Unit* summoner) override{
			if (!pInstance)
				return;
			Reset();			
		}

		void JustSummoned(Creature* summon)
		{
			if (!pInstance)
				return;
			if (Creature* pnefariand = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_NEFARIAN)))
				if (pnefariand->isInCombat())
					summon->SetInCombatWithZone();
		}

		void UpdateAI(const uint32 diff)
		{
			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent()){
				switch (eventId)
				{
					case 1:
						DoCast(me, 66318);
						events.ScheduleEvent(1, 5000);
						break;
				}
			}
			
		}
	};
};

/*######
## spell_nefarian_tail_lash - 77827
######*/

class spell_nefarian_tail_lash : public SpellScriptLoader
{
    public:
        spell_nefarian_tail_lash() : SpellScriptLoader("spell_nefarian_tail_lash") { }

        class spell_nefarian_tail_lash_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_nefarian_tail_lash_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                if (targets.empty())
                    return;

				struct check_for_position
				{
					Unit* uOwner;
					bool operator()(WorldObject* target)
					{
						if (!uOwner->isInBack(target, 0.872664f))
							return true;
						return false;
					}
				};
				
				if (Unit* owner = GetCaster())
				{
					targets.remove(owner);
					check_for_position is_not_in_front;
					is_not_in_front.uOwner = owner;
					targets.remove_if(is_not_in_front);
					//float arc = (50 * 3.141592791f) / 180; //45 grados en radianes en el frente y en la espalda del boss no puede tomar daño
					//for (std::list<WorldObject*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
					//{
					//	if (*itr)
					//	{
					//		if (!owner->isInBack(*itr, arc))
					//		{
					//			targets.remove((*itr));
					//		}
					//	}
					//}
				}
            }

            void Register()
            {
				OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_nefarian_tail_lash_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
				OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_nefarian_tail_lash_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_nefarian_tail_lash_SpellScript();
        }
};
            
class spell_onyxia_lightning_discharge : public SpellScriptLoader
{
    public:
        spell_onyxia_lightning_discharge() : SpellScriptLoader("spell_onyxia_lightning_discharge") { }

        class spell_onyxia_lightning_discharge_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_onyxia_lightning_discharge_SpellScript);

             void CalculateDamage(SpellEffIndex /*effIndex*/)
             {
                if (!GetHitUnit())
                    return;
				float arc = (50.0f * 3.141592791f)/ 180.0f; //45 grados en radianes en el frente y en la espalda del boss no puede tomar daño
				if (GetCaster()->isInFront(GetHitUnit(), arc) || GetCaster()->isInBack(GetHitUnit(), arc))
                    SetHitDamage(0);
				else{
					float power = GetCaster()->GetPower(POWER_ALTERNATE_POWER);
					if (power < 100){
						float damage = GetHitDamage();						
						float amount = (damage * float(power / 100.0f));						
						SetHitDamage(damage + amount);
					}
					else{
						SetHitDamage(0);
						GetCaster()->CastSpell(GetHitUnit(),78999); //Electrical Overload
					}
				}
             }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_onyxia_lightning_discharge_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_onyxia_lightning_discharge_SpellScript();
        }
};

//79492 Summon 
class spell_brushfire_summon_flashpoint : public SpellScriptLoader
{
public:
	spell_brushfire_summon_flashpoint() : SpellScriptLoader("spell_brushfire_summon_flashpoint") { }

	class spell_brushfire_summon_flashpoint_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_brushfire_summon_flashpoint_SpellScript);

		void SummonPos(SpellEffIndex /*effIndex*/)
		{
			/*WorldLocation summonPos = *GetExplTargetDest();
			
			if (Creature* nefarian = GetCaster()->ToCreature()){				
				nefarian->SummonCreature(54254, summonPos.GetPositionX(), summonPos.GetPositionY(), summonPos.GetPositionZ(), summonPos.GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN);				
			}	*/		
		}

		void Register()
		{
			OnEffectHit += SpellEffectFn(spell_brushfire_summon_flashpoint_SpellScript::SummonPos, EFFECT_0, SPELL_EFFECT_SUMMON);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_brushfire_summon_flashpoint_SpellScript();
	}
};

//81031
class spell_shadownblaze_spark : public SpellScriptLoader
{
public:
	spell_shadownblaze_spark() : SpellScriptLoader("spell_shadownblaze_spark") { }

	class spell_shadownblaze_spark_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_shadownblaze_spark_SpellScript);

		void SummonPos(SpellEffIndex /*effIndex*/)
		{
			if (const WorldLocation* pos = GetExplTargetDest())
			{
				if (Unit* caster = GetCaster()){	
					for (uint8 i = 0; i < 2; i++){
						caster->SummonCreature(54254, pos->GetPositionX(), pos->GetPositionY(), pos->GetPositionZ(), 0, TEMPSUMMON_DEAD_DESPAWN);
					}
				}
					
			}
		}

		void Register()
		{
			OnEffectHit += SpellEffectFn(spell_shadownblaze_spark_SpellScript::SummonPos, EFFECT_0, SPELL_EFFECT_TRIGGER_MISSILE);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_shadownblaze_spark_SpellScript();
	}
};

//npc_shadowblaze - Aura - 79396 / hace trigger al spell 81007  
class aura_brushfire_burn : public SpellScriptLoader
{
public:
	aura_brushfire_burn() : SpellScriptLoader("aura_brushfire_burn") { }

	class aura_brushfire_burn_AuraScript : public AuraScript
	{
		PrepareAuraScript(aura_brushfire_burn_AuraScript);

		void OnPeriodic(constAuraEffectPtr /*aurEff*/)
		{
			if (Unit* caster = GetCaster()){								
				caster->CastSpell(caster, 81007, true);
			}
		}

		void Register()
		{
			OnEffectPeriodic += AuraEffectPeriodicFn(aura_brushfire_burn_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
		}
	};

	AuraScript* GetAuraScript() const
	{
		return new aura_brushfire_burn_AuraScript();
	}
};


void AddSC_boss_bd_nefarian()
{
    new boss_bd_nefarian();
    new boss_bd_onyxia();
    new npc_nefarian_intro();
    new npc_animated_bone_warrior();
    new npc_chromatic_prototype();
    new npc_shadowflame_flashfire();
    new npc_shadowblaze();
    new spell_nefarian_tail_lash();
    new spell_onyxia_lightning_discharge();
	new npc_firefloor();
	new spell_shadownblaze_spark();
	new spell_brushfire_summon_flashpoint();
	new aura_brushfire_burn();
}
