/**
 * @file
 *
 * @brief This file manages a S.N.A.P. protocol implementation.
 *
 * @author               Andrew Cooper
 *
 *
 *
 */

/* Copyright (c) 2010 Andrew Cooper. All rights reserved.
 */

//_____  I N C L U D E S _______________________________________________________


#include "snap.h"
#include "lib_mcu/usart/usart.h"

//_____ M A C R O S ____________________________________________________________


//_____ V A R I A B L E S ______________________________________________________

static enum snap_states state;

static union HDB2 hdb2;
static union HDB1 hdb1;
static short hdb_cnt;
static short dab_cnt;
static short sab_cnt;
static short pfb_cnt;
static short db_cnt;
static short crc_cnt;

//_____ D E F I N I T I O N S __________________________________________________

void process_packet( void );

/**
 * @brief Initialize S.N.A.P processing task
 */
void snap_task_init( void )
{

}

/**
 * @brief
 */
void snap_task( void )
{
    unsigned char frame;

    if( USART0_RTR() )
    {
        frame = USART0_Receive();

        switch( state )
        {
            case kSnapPreamble :
            case kSnapSync :
                if( SYNC == frame )
                {
                    state = kSnapHeaderDef;
                    hdb_cnt = 0;
                }
                break;
            case kSnapHeaderDef :
                if( 0 == hdb_cnt )
                {
                    hdb_cnt = 1;
                    hdb2.raw = frame;
                }
                else
                {
                    hdb_cnt = 2;
                    hdb1.raw = frame;
                    if( DAB_0 == hdb2.fields.DAB )
                    {
                        if( SAB_0 == hdb2.fields.SAB )
                        {
                            if( PFB_0 == hdb2.fields.PFB )
                            {
                                if( NDB_0 == hdb1.fields.NDB )
                                {
                                    if( EDM_NONE == hdb1.fields.NDB )
                                    {
                                        process_packet();
                                    }
                                    else
                                    {
                                        state = kCRC;
                                    }
                                }
                                else
                                {
                                    state = kData;
                                }
                            }
                            else
                            {
                                state = kProtocol;
                            }
                        }
                        else
                        {
                            state = kSource;
                        }
                    }
                    else
                    {
                        state = kDestination;
                    }

                }

            case kDestination :
            case kSource :
            case kProtocol :
            case kData :
            case kCRC :
                break;
        }
    }
}

void process_packet()
{
}
