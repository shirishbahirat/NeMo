//
// Created by Mark Plagge on 8/18/17.
//

#ifndef SUPERNEMO_DUMPI_H
#define SUPERNEMO_DUMPI_H

#include "globals.h"

#define DEBUG 1
/** DUMPI TEXT FILE PERMS
 * <mpiType> <src> <dst> <wallStart> <wallStop> <cpuStart>
 * <cpuStop> <count> <dataType> <comm> <tag>
 */


/**
 * returns an Isend in dumpi format.
 * @param sourceChip The soruce chip - will be converted to an mpi rank
 * @param destChip The destination chip - will be converted to an mpi rank
 * @param twTimeSend -DUMPI start
 * @return A char (dynamic mem) containing the full dumpi line.
 */
char * generateIsend(long sourceChip, long destChip,  double twTimeSend);

/**
 * returns an Irecv in dumpi format.
 * @param sourceChip The soruce chip - will be converted to an mpi rank
 * @param destChip The destination chip - will be converted to an mpi rank
 * @param start -DUMPI start
 * @param stop -DUMPI end
 * @return A char (dynamic mem) containing the full dumpi line.
 */
char * generateIrecv(long sourceChip, long destChip, double twTimeSend);


void saveMPIMessage(id_type sourceCore, id_type destCore, double twTimeSend,
                    FILE * outputFile);

size_type coreToChip(size_type coreID);

size_type coreToRank(size_type coreID);

bool isDestInterchip(id_type core1, id_type core2);

#endif //SUPERNEMO_DUMPI_H
