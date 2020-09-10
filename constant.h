#ifndef CONSTANT_H
#define CONSTANT_H
#include<QtMath>
//数据类型，用于setData存储数据
enum DataType{entityType,detailType};
//对应数据类型entityTpe
enum EntityType{characterType,enemyType,landType,deadZone,checkPoint,trapType,propType,airWall};
//对应lantype的detailtype
enum LandType{normalLand,spikeLand,movingLand,springLand,fragileLand,hintLand};
//
enum EnemyType{worm1,worm2,worm3};
//动画模式
enum animeMode{relaxMode,moveMode,jumpMode,attackMode,dieMode,skillMode};
//方位
enum moveDirection{moveLeft,moveRight,cancelLeft,cancelRight};

enum CharacterType{silver,exusiai,sheep};

enum TrapType{enemyGenerator,hidenTrap};

enum PropType{mushRoom,flower};
static qreal g=10;//模拟重力加速度
static int fps=60;//帧数
//typenum,用于给每个大类型的小细节编号
//landtype:normalland:0
#endif // CONSTANT_H
