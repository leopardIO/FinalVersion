/*
 * =====================================================================================
 *
 *       Filename:  k_means.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/05/12 00:14:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  liangyao(ly), liangyao.ndsl@gmail.com
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */

#ifndef K_MEANS_H
#define K_MEANS_H

#include "surflib.h"
#include <iostream>

#define ITER_TIMES 300
#define MIN_KMEANS_DISTANCE 0.1

class Kmeans
{
    private:
        unsigned int m_iterTime;
        unsigned int m_branch;
        IpVec  *ipts;

    private:
        Kmeans(const Kmeans& );
        Kmeans& operator= (const Kmeans& );
       
        float getDistance(Ipoint &ip1, Ipoint &ip2);
        void setData(IpVec *ipts);
        void initCenters();
        void assignToClusters();
        void updataCenters();
        double getSumDistance();

    public:
        IpVec  **m_clusters;
        IpVec  m_centers;
   
    public:
        Kmeans(int branch);
        ~Kmeans();
        void run(IpVec *ipts);
};

#endif
