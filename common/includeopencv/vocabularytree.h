/*
 * =====================================================================================
 *
 *       Filename:  vocabularytree.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/31/12 01:14:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  liangyao(ly), liangyao.ndsl@gmail.com
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */

#ifndef VOCABULARYTREE_H
#define VOCABULARYTREE_H

#include "k_means.h"
#include <map>
#include <list>
#include <fstream>
#include <dirent.h>
#include <sys/time.h>
#include <algorithm>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>

#define VOCABULARYTREE_BRANCH  10
#define VOCABULARYTREE_LEVEL 6 
#define PIC_SIZE 600
#define SURF_PARA 0.0004f

using namespace cv;
using namespace std;

typedef map<string, unsigned int>  Hi_gram;
typedef map<string, double> Re_index;

typedef struct _vc_node
{
    uint32_t id;       
    Ipoint center;       
    struct _vc_node **child;   
    bool leaf;     
    Re_index reverse_index;   

    _vc_node()
    {
        id = 0;
        leaf = false;
        child = NULL;
    }
}vctree_node,*vctree;

struct PairCompare
{
    bool operator() (const pair<string, double> &lhs,
            const pair<string, double> &rhs)
    {
        return lhs.second > rhs.second;
    }
};

struct PointDisCompare
{
    bool operator() (const pair<int, float> &lhs, 
            const pair<int, float> &rhs)
    {
        return lhs.second < rhs.second;
    }
};

class VocabularyTree
{

  public:

      VocabularyTree(unsigned int branch = VOCABULARYTREE_BRANCH,
              unsigned int level = VOCABULARYTREE_LEVEL):
          m_branch(branch), m_level(level),m_nodeID(0),
          m_picSum(0), m_vctree(NULL)
    {

    }

      void training(const char* dataDir, const char* featureDir);
      int matchPic (IpVec &ipts, vector<pair<string, double> > &result); 
      void writeVocabularyTree(ofstream &);
      void readVocabularyTree(ifstream &);
      void deleteVocabularyTree();
      ~VocabularyTree();

  private:

      VocabularyTree(const VocabularyTree &) {}
      VocabularyTree& operator=(const VocabularyTree &) {}

      Re_index getIndex(IpVec *);
      uint32_t inline generateID(); 
      void preoder(vctree ) const;
      IpVec* getIpts(const char* dataDir, const char* featureDir);
      vctree buildTree(vctree &, IpVec *&, Ipoint&, int);
      void buildVocabularyTree(IpVec*);
      void nodeWrite(vctree &, ofstream &); 
      void nodeRead(vctree &, ifstream &);
      void writeTree(vctree &, ofstream &);
      void readTree(vctree&, ifstream &);
      int searchTree(Ipoint &, vctree , Re_index &);
      int sortValue(Re_index & ,vector<pair<string,double> > &);
      void deleteTree(vctree &); 

  private:

       vctree m_vctree;
       unsigned int m_branch;
       unsigned int m_level; 
       unsigned int m_picSum;
	   uint32_t m_nodeID;
       map<unsigned int, string> m_filesIndex;
};

#endif
