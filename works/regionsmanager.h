/**
 * @file regionsmanager.h
 * @brief file use for managed regions class
 * @copyright 2015 Jean-Jacques PONCIANO, Claire PRUDHOMME
 * All rights reserved.
 * This file is part of scn reader.
 *
 * scn reader is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * scn reader is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>
 * @author Jean-Jacques PONCIANO and Claire PRUDHOMME
 * Contact: ponciano.jeanjacques@gmail.com
 * @version 0.1
 */
#ifndef REGIONSMANAGER_H
#define REGIONSMANAGER_H

#include "region.h"
class RegionsManager
{
public:
    RegionsManager();
    /**
     * @brief RegionsManager
     * @param distanceMax maximum distance between two points in a same region
     * @param minsize minimum size of a region for detect a merge
     * @param neighborsDistance distance between neighbors
     * @param maxSize maximum number of points that a region may contain
     */
    RegionsManager(float distanceMax, int minsize,float neighborsDistance, int maxSize);
    ~RegionsManager();
    Region getRegion(int ID);
    void remove(int ID);
    /**
     * @brief removeRegions it removes regions and it tests if a region is not too small for die
     * @param RegionsID identifier of the regions to be removed
     * @return true if no region was too small
     */
    bool removeRegions(QVector<int> RegionsID);
    /**
     * @brief split split a region in two regions
     * @param regionID identifier of the region to be splited
     */
    void split(int regionID);
    /**
     * @brief intoRegions test  if the point belongs to the region
     * @param pt point to be tested.
     * @return identifiers of each region containing the point
     */
    QVector<int> intoRegions(PointGL currentPoint);
private:
    int generatingID();
    QVector<Region>regions;
    int nbregions;
     int maxSize;
float distanceMax;
int minSize;
float neighborsDistance;
};

#endif // REGIONSMANAGER_H
