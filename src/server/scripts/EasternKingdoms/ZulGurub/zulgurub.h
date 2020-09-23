#ifndef DEF_ZULGURUB_H
#define DEF_ZULGURUB_H

#define ZGScriptName "instance_zulgurub"

uint32 const EncounterCount = 5;

enum DataTypes
{
    DATA_VENOXIS            = 0,
    DATA_MANDOKIR           = 1,
    DATA_KILNARA            = 2,
    DATA_ZANZIL             = 3,
    DATA_JINDO              = 4,

    // Cache of Madness
    DATA_HAZZARAH           = 5,
    DATA_RENATAKI           = 6,
    DATA_WUSHOOLAY          = 7,
    DATA_GRILEK             = 8,
    DATA_BOSSES             = 9,

	// Jin'do the Godbreaker
	DATA_JINDOR_TRIGGER = 10,
	DATA_POSITION_ID = 11,
	DATA_TIKI_MASK_ID = 12,
};

enum CreatureIds
{
    NPC_VENOXIS             = 52155,
    NPC_MANDOKIR            = 52151,
    NPC_KILNARA             = 52059,
    NPC_ZANZIL              = 52053,
    NPC_JINDO               = 52148,

    // Cache of Madness
    NPC_HAZZARAH            = 52271,
    NPC_RENATAKI            = 52269,
    NPC_WUSHOOLAY           = 52286,
    NPC_GRILEK              = 52258,


	// Jin'do the Godbreaker
	NPC_JINDO_TRIGGER = 52150,
	NPC_SHADOW_OF_HAKKAR = 52650,

	NPC_GAS_CLOUD = 52062,
	NPC_HAKKAR_RIFT = 52400,
	NPC_MADNESS_CONTROLLER = 91004,
	NPC_TROLL_ARTIFACT_STAND = 52452,
	NPC_ELF_ARTIFACT_STAND = 52450,
	NPC_DWARF_ARTIFACT_STAND = 52446,
	NPC_TROLL_ARTIFACT_SUM = 52453,
	NPC_ELF_ARTIFACT_SUM = 52451,
	NPC_DWARF_ARTIFACT_SUM = 52449,
	NPC_CAVE_IN_TRIGGER = 52387,

	// Venoxis
	NPC_GENERAL_PURPOSE_BUNNY = 45979,
	NPC_BLOOD_VENOM = 52525,
	NPC_VENOMOOUS_EFFUSION = 52288,
};

enum GameObjectIds
{
    GO_VENOXIS_EXIT     = 208844,
    GO_MANDOKIR_EXIT1   = 208845,
    GO_MANDOKIR_EXIT2   = 208846,
    GO_MANDOKIR_EXIT3   = 208847,
    GO_MANDOKIR_EXIT4   = 208848,
    GO_MANDOKIR_EXIT5   = 208849,
    GO_ZANZIL_EXIT      = 208850,
    GO_KILNARA_EXIT     = 180497,
	// Cache of Madness
	GO_THE_CACHE_OF_MADNESS_DOOR = 208843,
};

enum OtherSpells
{
    SPELL_FROSTBURN_FORMULA = 96331,
    SPELL_HYPPOTHERMIA      = 96332,
};

template<class AI>
CreatureAI* GetZulGurubAI(Creature* creature)
{
	if (InstanceMap* instance = creature->GetMap()->ToInstanceMap())
	if (instance->GetInstanceScript())
	if (instance->GetScriptId() == sObjectMgr->GetScriptId(ZGScriptName))
		return new AI(creature);
	return NULL;
}

#endif

