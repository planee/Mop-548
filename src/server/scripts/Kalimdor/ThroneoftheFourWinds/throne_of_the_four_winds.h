#ifndef DEF_THRONEOFTHEFOURWINDS_H
#define DEF_THRONEOFTHEFOURWINDS_H

#define TotFWScriptName "instance_throne_of_the_four_winds"

enum Data
{
    DATA_CONCLAVE_OF_WIND,
    DATA_ALAKIR_EVENT,

	MAX_BOSSES,

	DATA_ALAKIR_FLIGHT_PHASE,
	DATA_GATHERING_STRENGTH,
	DATA_WEATHER_EVENT,
};

enum Data64
{
	DATA_ANSHAL,
	DATA_NEZIR,
	DATA_ROHASH,
	DATA_ALAKIR,
};

enum Creatures
{
    NPC_ANSHAL  = 45870,
    NPC_NEZIR   = 45871,
    NPC_ROHASH  = 45872,
    NPC_ALAKIR  = 46753,
	

	// Al'akir

	NPC_SLIPSTREAM_ALAKIR = 47066,
	NPC_SQUILL_LINE_1 = 48852,
	NPC_SQUILL_LINE_2 = 47034,
	NPC_SQUILL_1 = 48855,
	NPC_SQUILL_2 = 48854,
	NPC_ICE_STORM_RAIN = 46734,
	NPC_LIGHTNING_STRIKE_TRIGGER = 48977,
	NPC_STORMLING = 47175,
	NPC_STORMLING_PRE_EFFECT = 47177,
	NPC_LIGHTNING_CLOUD_TRIGGER = 48190,
	NPC_LIGHTNING_CLOUD_TRIGGER_EXTRA = 48196,
	NPC_LIGHTNING_CLOUD_TRIGGER2 = 51597,
	NPC_RELENTLESS_STORM = 47807,
	NPC_RELENTLESS_STORM_VEHICLE = 47806,
	NPC_ICE_STORM_ROTATE_TRIGGER = 46766,
	NPC_WIND_BURST_TRIGGER = 8777000,
	NPC_WIND_BURST_INSTANT_TRIGGER = 8885800,
	NPC_SLIPSTREAM_ALAKIR_1 = 46045,
	NPC_WORLD_TRIGGER = 36171,
	NPC_ICE_STORM = 46973,
};
enum GobjectIds
{
	GO_SKYWALL_RAID = 207737,
	GO_SKYWALL_WIND = 223271,
	GO_HEART_OF_WIND_10 = 207891,
	GO_HEART_OF_WIND_25 = 207892,
	GO_HEART_OF_WIND_10H = 207893,
	GO_HEART_OF_WIND_25H = 207894,
};

enum Platforms
{
	GO_NAZIR_PLATFORM = 206700,
	GO_ANSHAL_PLATFORM = 206699,
	GO_ROHASH_PLATFORM = 206701,
};

enum InstanceSpells
{
	SPELL_PRE_COMBAT_EFFECT_ANSHAL = 85537,
	SPELL_PRE_COMBAT_EFFECT_NEZIR = 85532,
	SPELL_PRE_COMBAT_EFFECT_ROHASH = 85538,
};

enum InstanceDataMisc
{
	DATA_START_HELP_PLAYER,
};
const Position startPos = {-266.834991f, 816.938049f, 200.0f, 0.0f};
const Position rohashPos = {-51.4635f, 576.25f, 200.1f, 1.51f}; // for tornado

#endif
