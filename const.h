#ifndef CONST_H
#define CONST_H

#endif // CONST_H

enum TressItemType{
    TreeItemPro = 1,//表示项目条目 根目录
    TreeItemDir = 2,//表示项目的文件夹
    TreeItemPic=3,//表示项目的图片
};

//播放状态 静止状态
enum PicBtnState{
    PicBtnStateNormal=1,
    PicBtnStateHover=2,
    PicBtnStatePress=3,

    PicBtnStateNormal2=4,
    PicBtnStateHover2=5,
    PicBtnStatePress2=6,
};

const int PROGRESS_WIDTH = 300;
const int PROGRESS_MAX=300;
const int PREITEM_SIZE=100;
const int PREICON_SIZE=90;
