/*
 * =====================================================================================
 *
 *       Filename:  interface.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/21/2013 03:20:11 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  liangyao (ly), liangyao.ndsl@gmail.com 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */
#ifndef INTERFACE_H
#define INTERFACE_H

#include "matchpic.h"
#include "testtool.h"

class Matcher
{
public:
    Matcher(){}
    
    /* *
     * @brief  训练 
     *
     * @param trainDataDir 存放训练样本图片的文件夹（全）路径
     * @param featureDataDir 存放样本图片特征数据的文件夹（全）路径
     * @param indexPath 存放索引文件的（全）路径 
     *
     * @return  
     *      - 
     * */ 
    void train(const char* trainDataDir, 
            const char* featureDataDir, const char* indexPath);
   
    /* *
     * @brief  重新训练
     *
     * @param trainDataDir 存放训练样本图片的文件夹（全）路径
     * @param featureDataDir 存放样本图片特征数据的文件夹（全）路径
     * @param indexPath 存放索引文件的（全）路径 
     *
     * @return  
     *      - 
     * */ 
    void reTrain(const char* trainDataDir, 
            const char* featureDataDir, const char* indexPath);
     
    /* *
     * @brief  加载索引 
     *
     * @param indexPath 存放索引文件的（全）路径 
     *
     * @return  
     *      - 
     * */ 
    void loadIndex(const char* indexPath);
    
    /* *
     * @brief  匹配(单张) 
     *
     * @param matchSignPath 待匹配图片的（全）路径 
     * @param featureDataDir 存放样本图片特征数据的文件夹（全）路径
     * @param trainDataDir 存放样本图像集的文件夹（全）路径
     *
     * @return  
     *      - 匹配文件名 +　画框点集（以＆＆分隔） 
     * */ 
    string match(const char* matchSignPath, const char* featureDataDir, 
            const char* trainDataDir);
    
    /* *
     * @brief  匹配(批量) for test
     *
     * @param matchDir 待匹配图片的文件夹（全）路径 
     * @param featureDataDir 存放样本图片特征数据的文件夹（全）路径
     *
     * @return  
     *      - 
     * */ 
    void matchDir(const char* matchDir,
            const char* featureDataDir, const char* trainDataDir);

private:
    Matcher(const Matcher &);
    Matcher& operator = (const Matcher &);

private:
    VocabularyTree m_vcTree;
    PicMatch m_pMatch;
};

#endif
