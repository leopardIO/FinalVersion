/*
 * =====================================================================================
 *
 *       Filename:  matchpic.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  9/31/13 01:14:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  liangyao(ly), liangyao.ndsl@gmail.com
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */

#ifndef PICMATCH_H
#define PICMATCH_H

#include "testtool.h"
#include "vocabularytree.h"
#include <opencv2/contrib/contrib.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/gpu/gpu.hpp>
#include "LRU.h"

#define USE_GPU 0

const float WORST_DISTANCE = 0.3;
const float RATIO_THRESHOLD = 0.75; 

class PicMatch
{

private:
    LRU m_lru;
    enum {FILTER_NUM = 10, RE_SEARCH_NUM = 10, MIN_LENGTH = 80}; 
private: 
    PicMatch(const PicMatch&) {}
    PicMatch& operator=(const PicMatch &) {}
   
    int getMatchNum(IpVec &source_ipts, IpVec &match_ipts);
    int matchFunc(IpVec &source_ipts, IpVec &match_ipts, vector<DMatch> &);
    string preMatch(Mat &mat, IpVec &source_ipts, const char* featureDir,
            const char* trainDataDir); 
    int drawRectAngle(Mat &, const string&, vector<KeyPoint> &, 
           vector<KeyPoint> &,vector<DMatch>& , vector<Point2f> &scene_corners);

public:
    PicMatch() {}
    string matchPic(const char* picName, const char* featureDir, 
            const char* trainDataDir, VocabularyTree &vc_tree);
};

#endif
