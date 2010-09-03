/**
 * @file
 *
 * @brief Constants and structure definitions for S.N.A.P.
 *
 */

#if !defined( _SNAP_H_ )
#define _SNAP_H_

#include <stdint.h>
/**
 * @brief Synchronization Byte
 *
 * This byte is pre-defined to 01010100b and indicates the start of each packet.
 */
#define SYNC ( (uint8_t) 0x54)

/**
 * @brief Header Definition Byte 2
 *
 * The first two bytes after the synchronization byte are called header definition bytes, they are used to
 * define the structure of the complete packet. The name on the fields are chosen to be easy to
 * remember.
 *
 * <PRE>
 * Bit 7 6|5 4|3 2|1 0
 *     D D|S S|P P|A A
 *      D | S | P | A
 *      A | A | F | C
 *      B | B | B | K
 * </PRE>
 * DAB = Number of Destination Address Bytes
 * SAB = Number of Source Address Bytes
 * PFB = Number of Protocol specific Flag Bytes
 * ACK = ACK/NAK bits
 */
union HDB2
{
    struct HDB2_fields
    {
        /** @brief Number of Destination Address Bytes
         *
         * These two bits defines number of destination address bytes in the packet. With the maximum size of
         * 3 Bytes it gives a total of 16 777 215 different destination node addresses.
         */
        uint8_t DAB :2;

        /** @brief Number of Source Address Bytes
         *
         * These two bits defines the number of source address bytes in the packet. With the maximum size of
         * 3 Bytes, it gives a total of 16 777 215 different source node addresses.
         */
        uint8_t SAB :2;

        /** @brief Number of Protocol specific Flag Bytes
         *
         * These two bits defines how many protocol specific flag bytes the packet includes, from 0-3 Bytes
         * which give a total of 24 flags.
         */
        uint8_t PFB :2;

        /** @brief ACK/NAK bits
         *
         * These two bits defines if the sending node requests an ACK/NAK packet in return. These bits also
         * acts as the actual ACK/NAK response sent from the receiving node.
         */
        uint8_t ACK :2;
    } fields;

    /** @brief Raw Access to HDB2 byte
     *
     */
    uint8_t raw;
};

/// 0 Byte destination address
#define DAB_0   ((uint8_t) 0)
/// 1 Byte destination address
#define DAB_1   ((uint8_t) 1)
/// 2 Byte destination address
#define DAB_2   ((uint8_t) 2)
/// 3 Byte destination address
#define DAB_3   ((uint8_t) 3)

/// 0 Byte source address
#define SAB_0   ((uint8_t) 0)
/// 1 Byte source address
#define SAB_1   ((uint8_t) 1)
/// 2 Byte source address
#define SAB_2   ((uint8_t) 2)
/// 3 Byte source address
#define SAB_3   ((uint8_t) 3)

/// 0 Byte flags
#define PFB_0   ((uint8_t) 0)
/// 1 Byte flags
#define PFB_1   ((uint8_t) 1)
/// 2 Byte flags
#define PFB_2   ((uint8_t) 2)
/// 3 Byte flags
#define PFB_3   ((uint8_t) 3)

/// No ACK request (Tx)
#define ACK_NONE    ((uint8_t) 0)
/// ACK request (Tx)
#define ACK_REQ     ((uint8_t) 1)
/// ACK response (Rx)
#define ACK_RESP    ((uint8_t) 2)
/// NAK response (Rx)
#define NAK_RESP    ((uint8_t) 3)

/**
 * @brief Header Definition Byte 1
 *
 * The first two bytes after the synchronization byte are called header definition bytes, they are used to
 * define the structure of the complete packet. The name on the fields are chosen to be easy to
 * remember.
 *
 * <PRE>
 * Bit 7|6 5 4|3 2 1 0
 *     C|E E E|N N N N
 *     C|  E  |   N
 *     M|  D  |   D
 *     D|  M  |   B
 * </PRE>
 *
 * CMD = CoMmanD mode bit
 * EDM = Error Detection Method
 * NDB = Number of Data Bytes
 */
union HDB1
{
    struct HDB1_fields
    {
        /** @brief Bit 7 - Command mode bit
         *
         * This bit indicates what's called command mode. This is an optional feature and if a node is not
         * implementing it this bit should always be set to zero (CMD=0).
         *
         * A node implementing this feature will be able to respond on queries from other nodes as well as
         * send responses when for example the receiving node can't handle the packet structure in a received
         * packet. It can be used to scan large networks for nodes and have them respond with their
         * capabilities or for two nodes negotiating the right packet structure, among other things.
         *
         * If this bit is set (CMD=1) it indicates that the data in DB1 contains a command (query or a
         * response). This results in total 256 different commands.
         *
         * The range is divided in two half's, commands between 1-127 are queries and commands between
         * 128-255 are responses. The commands specified to date are the following. Note this is the value in
         * DB1, not the actual CMD bit.
         *
         * There are some things to think about for this to work properly. The sending node can not use an
         * higher address range than the receiving node. This is not a problem if the receiving nodes that are
         * implementing this feature are capable to handle all the address range (i.e. 1-16 777 215). Another
         * solution is to assign all masters in the network (in a master/slave network) to the low address range
         * (i.e. between 1-255).
         */
        uint8_t CMD :1;

        /** @brief Bit 6 to 4 - Error Detection Method (EDM)
         *
         * These three bits defines what kind error detecting method is being used to validate the packet. A
         * node does not need to support any error detection method at all (i.e. EDM = 0) or you can choose to
         * implement a subset or all of them. For more information about this topic see section 2.6.
         *
         * <PRE>
         * Bit 6 5 4
         *     0 0 0    No error detection
         *     0 0 1    3 times re-transmission
         *     0 1 0    8-bit checksum
         *     0 1 1    8-bit CRC
         *     1 0 0    16-bit CRC
         *     1 0 1    32-bit CRC
         *     1 1 0    FEC (specific FEC standard TBD)
         *     1 1 1    User specified
         * </PRE>
         *
         * TBD = To Be Determined
         */
        uint8_t EDM :3;

        /** @brief Bit 3 to 0 - Number of Data Bytes (NDB)
         *
         * These four bits defines how many bytes data there is in the packet (0-512 Bytes).
         *
         * <PRE>
         * Bit 3 2 1 0
         *     0 0 0 0  0 Byte
         *     0 0 0 1  1 Byte
         *     0 0 1 0  2 Bytes
         *     0 0 1 1  3 Bytes
         *     0 1 0 0  4 Bytes
         *     0 1 0 1  5 Bytes
         *     0 1 1 0  6 Bytes
         *     0 1 1 1  7 Bytes
         *     1 0 0 0  8 Bytes
         *     1 0 0 1  16 Bytes
         *     1 0 1 0  32 Bytes
         *     1 0 1 1  64 Bytes
         *     1 1 0 0  128 Bytes
         *     1 1 0 1  256 Bytes
         *     1 1 1 0  512 Bytes
         *     1 1 1 1  User Specified
         * </PRE>
         */
        uint8_t NDB :4;
    } fields;

    /** @brief Raw Access to HDB2 byte
     *
     */
    uint8_t raw;
};

/** @brief No error detection
 *
 * This one is obvious. Packets will be sent without any error detection information at all.
 *
 * @sa HDB1::EDM
 */
#define EDM_NONE ((uint8_t) 0)

/** @brief 3 times re-transmission
 *
 * This is a very simple way of error detection that is very easy to implement. The sending node
 * sends the exact same packet three times.The receiving node just compare the received packets
 * and if 3 equal packets are received then the data is assumed to be OK.
 *
 * @sa HDB1::EDM
 */
#define EDM_3TX ((uint8_t) 1)

/** @brief 8-bit checksum
 *
 * This method adds one byte (8-bits) containing the checksum at the end of each packet. The
 * calculation of the checksum is simple and all that’s done is that all bytes (except the SYNC
 * byte) is summed together and the 8-bit result is the checksum byte. This is sometimes referred
 * as Longitudinal Redundancy Check (LRC) in some documentation.
 *
 * @sa HDB1::EDM
 */
#define EDM_CHKSUM8 ((uint8_t) 2)

/** @brief 8-bit CRC
 *
 * This method also adds one byte (8-bits) containing the checksum at the end of each packet.
 * The calculation of the CRC checksum is a bit more sophisticated than 8-bit checksum and
 * therefore this is a bit more reliable.
 *
 * X^8+X^5+X^4+1
 * Polynominal = h18
 * Initial remainder = h00
 *
 * @sa HDB1::EDM
 */
#define EDM_CRC8 ((uint8_t) 3)

/** @brief 16-bit CRC
 *
 * This method adds two bytes (16-bits) containing the checksum at the end of each packet.
 * The calculation of the CRC checksum is similar to 8-bit CRC but a bit more reliable due to the
 * increased size of the checksum (16-bits).
 *
 * X^16+X^12+X^5+1
 * Polynominal = h1021
 * Initial remainder = h0000
 *
 * @sa HDB1::EDM
 */
#define EDM_CRC16 ((uint8_t) 4)

/** @brief 32-bit CRC
 *
 * This method adds four bytes (32-bits) containing the checksum at the end of each packet.
 * The calculation of the CRC checksum is similar to 8-bit and 16-bit CRC but even more
 * reliable.
 *
 * X^32+X^26+X^23+X^22+X^16+X^12+X^11+X^10+X^8+X^7+X^5+X^4+X^2+X^1+1
 * Polynominal = h04C11DB7
 * Initial reminder = hFFFFFFFF
 *
 * @note The result is inverted.
 *
 * @sa HDB1::EDM
 */
#define EDM_CRC32 ((uint8_t) 5)

/** @brief FEC
 *
 * Specific FEC standard to be determined. FEC (Forward Error Correction) is often used in
 * simplex RF links since it offers the possibility to not only detect but also to correct corrupt
 * data. There are many different "standards" available.
 *
 * @sa HDB1::EDM
 */
#define EDM_FEC ((uint8_t) 6)

/** @brief User specified
 *
 * If none of the above error detection methods suits your application you can use your own.
 *
 * @sa HDB1::EDM
 */
#define EDM_USER ((uint8_t) 7)

/** @brief 0 bytes of data
 *
 */
#define NDB_0 ((uint8_t) 0)

/** @brief 1 bytes of data
 *
 */
#define NDB_1 ((uint8_t) 1)

/** @brief 2 bytes of data
 *
 */
#define NDB_2 ((uint8_t) 2)

/** @brief 3 bytes of data
 *
 */
#define NDB_3 ((uint8_t) 3)

/** @brief 4 bytes of data
 *
 */
#define NDB_4 ((uint8_t) 4)

/** @brief 5 bytes of data
 *
 */
#define NDB_5 ((uint8_t) 5)

/** @brief 6 bytes of data
 *
 */
#define NDB_6 ((uint8_t) 6)

/** @brief 7 bytes of data
 *
 */
#define NDB_7 ((uint8_t) 7)

/** @brief 8 bytes of data
 *
 */
#define NDB_8 ((uint8_t) 8)

/** @brief 16 bytes of data
 *
 */
#define NDB_16 ((uint8_t) 9)

/** @brief 32 bytes of data
 *
 */
#define NDB_32 ((uint8_t) 10)

/** @brief 64 bytes of data
 *
 */
#define NDB_64 ((uint8_t) 11)

/** @brief 128 bytes of data
 *
 */
#define NDB_128 ((uint8_t) 12)

/** @brief 256 bytes of data
 *
 */
#define NDB_256 ((uint8_t) 13)

/** @brief 512 bytes of data
 *
 */
#define NDB_512 ((uint8_t) 14)

/** @brief User specified bytes of data
 *
 */
#define NDB_USER ((uint8_t) 15)

/** @brief States of processing
 *
 * Based upon the next expected protocol member.
 *
 * In general, the states flow in order, though some fields in HDB1 and HDB2 can
 * cause some states to be skipped.
 */
enum snap_states
{
    kSnapPreamble, //!< kSnapPreamble
    kSnapSync,     //!< kSnapSync
    kSnapHeaderDef,//!< kSnapHeaderDef
    kDestination,  //!< kDestination
    kSource,       //!< kSource
    kProtocol,     //!< kProtocol
    kData,         //!< kData
    kCRC           //!< kCRC
};

#endif
