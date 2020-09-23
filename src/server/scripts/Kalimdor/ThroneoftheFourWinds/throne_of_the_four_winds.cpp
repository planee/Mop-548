#include "ScriptPCH.h"
#include "throne_of_the_four_winds.h"

enum SlipstreamEnums
{
    // Land Positions
    DIR_WEST_TO_SOUTH,
    DIR_SOUTH_TO_WEST,
    DIR_NORTH_TO_WEST,
    DIR_WEST_TO_NORTH,
    DIR_EAST_TO_NORTH,
    DIR_NORTH_TO_EAST,
    DIR_SOUTH_TO_EAST,
    DIR_EAST_TO_SOUTH,
    DIR_ERROR,

    // Spells
    SPELL_SLIPSTREAM_BUFF           = 87740,
    SPELL_SLIPSTREAM_PLAYER_VISUAL  = 85063,
	SPELL_SLIPSTREAM_AURA           = 87713,
};

Position const SlipstreamPositions[8] =
{
    {-237.766510f, 865.409668f, 196.9f, 0.0f},
    {-96.677574f, 1004.523499f, 196.9f, 0.0f},
    {2.173538f, 1002.027039f, 196.9f, 0.0f},
    {137.942337f, 865.361328f, 196.9f, 0.0f},
    {138.479660f, 763.253662f, 196.9f, 0.0f},
    {-1.872189f, 625.810364f, 196.9f, 0.0f},
    {-100.733566f, 626.520081f, 196.9f, 0.0f},
    {-237.336517f, 765.919495f, 196.9f, 0.0f}
};

class npc_throne_of_the_four_winds_slipstream : public CreatureScript
{
    public:
        npc_throne_of_the_four_winds_slipstream() : CreatureScript("npc_throne_of_the_four_winds_slipstream") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_throne_of_the_four_winds_slipstreamAI (pCreature);
        }

        struct npc_throne_of_the_four_winds_slipstreamAI : public Scripted_NoMovementAI
        {
            npc_throne_of_the_four_winds_slipstreamAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);

                m_uiSlipstreamPosition = 8;

                for (uint8 i = 0; i <= 7; ++i)
                    if (me->GetDistance2d(SlipstreamPositions[i].GetPositionX(), SlipstreamPositions[i].GetPositionY()) < 10)
                    {
                        m_uiSlipstreamPosition = i;
                        break;
                    }

                    if (m_uiSlipstreamPosition >= DIR_ERROR)
                        return;

                m_uiSlipstreamPosition += (m_uiSlipstreamPosition == DIR_WEST_TO_SOUTH || m_uiSlipstreamPosition == DIR_NORTH_TO_WEST ||
                    m_uiSlipstreamPosition == DIR_EAST_TO_NORTH || m_uiSlipstreamPosition == DIR_SOUTH_TO_EAST ) ? 1 : -1;
				// Assign linked Boss and Slipstream to disabled slipstreams if the bosses casts Ultimate
			}

            void MoveInLineOfSight(Unit* who)
            {
                if(m_uiSlipstreamPosition >= DIR_ERROR || who->GetTypeId() != TYPEID_PLAYER)
                    return;

                if (who->GetExactDist(me) <= 10.f && !who->HasAura(SPELL_SLIPSTREAM_BUFF))
                {
                    me->AddAura(SPELL_SLIPSTREAM_BUFF, who);
                    me->AddAura(SPELL_SLIPSTREAM_PLAYER_VISUAL,who);

                    // if we use the motion master only to relocate the player
                    // it will cause bugs
                    if (who->GetOrientation() != SlipstreamPositions[m_uiSlipstreamPosition].GetOrientation())
				        who->RemoveAurasWithInterruptFlags(AURA_INTERRUPT_FLAG_TURNING);

				    me->GetMap()->PlayerRelocation(who->ToPlayer(),SlipstreamPositions[m_uiSlipstreamPosition].GetPositionX(), SlipstreamPositions[m_uiSlipstreamPosition].GetPositionY(),SlipstreamPositions[m_uiSlipstreamPosition].GetPositionZ(), SlipstreamPositions[m_uiSlipstreamPosition].GetOrientation());

                    who->GetMotionMaster()->MoveJump(SlipstreamPositions[m_uiSlipstreamPosition].GetPositionX(), SlipstreamPositions[m_uiSlipstreamPosition].GetPositionY(), 198.458481f, 1 ,6);
                }
            }
			
			/*void UpdateAI(uint32 const diff)
			{
				// The Slipstreams are Deactivated before each Ultimate ability

				if (linkedSlipstreamObject && linkedBoss)
				{


				}
				else if (isUltimate)
					isUltimate = false;

				if (!isUltimate != isActive)
				{
					if (isActive)
					{ // Activate Slipstream

						if (linkedSlipstreamObject)
							linkedSlipstreamObject->SetPhaseMask(PHASEMASK_NORMAL, true);

					}
					else
					{ // Deactivate Slipstream

						if (linkedSlipstreamObject)
							linkedSlipstreamObject->SetPhaseMask(2, true);
					}

					isActive = !isActive;
				}
			}*/
			
        private:

            uint8 m_uiSlipstreamPosition;
			bool isUltimate;
			bool isActive;
			GameObject* linkedSlipstreamObject;
			Unit* linkedBoss;
        };
};

class npc_slipstream_alakir : public CreatureScript
{
public:
	npc_slipstream_alakir() : CreatureScript("npc_slipstream_alakir") { }
	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_slipstream_alakirAI(pCreature);
	}
	bool OnGossipHello(Player* player, Creature* creature)
	{
		if (InstanceScript* pInstance = creature->GetInstanceScript())
		{
				player->TeleportTo(754, -115.186859f, 815.128662f, 191.101f, 0.02332f);
		}
		return false;
	}
	struct npc_slipstream_alakirAI : public Scripted_NoMovementAI
	{
		npc_slipstream_alakirAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
		{
			me->SetCanFly(true);
		}

		void Reset()
		{
			DoCast(me, SPELL_SLIPSTREAM_AURA);
			me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
		}

		void UpdateAI(const uint32 diff)
		{
		}
	};
};

void AddSC_throne_of_the_four_winds()
{
    new npc_throne_of_the_four_winds_slipstream();
	new npc_slipstream_alakir();
}
