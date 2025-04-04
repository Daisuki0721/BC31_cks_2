#ifndef _ADRAW_H_
#define _ADRAW_H_

#define ALLBOARD 0
#define SIDEBOARD 1
#define MAINBOARD 2

/*黑边圆角矩形按钮，非激活为0，激活为1*/
int rounded_button(int x1, int y1, int x2, int y2, int r, int color, int state);
/*黑边圆角矩形按钮(增量型带汉字）*/
void rounded_button_d(int x, int y, int xsize, int ysize, char * str, int r, int color);
/*黑边圆角矩形按钮(增量型），输出asc字符*/
void rounded_button_asc(int x, int y, int xsize, int ysize, char * str, int r, int color);
/**************************************
 * 在指定位置输出一个车牌头(使用prthz函数)
 * flag为车牌头代号，size为字号大小（可选16，24，32，48）
 * flag参数参考表：
 * 1 ：京    2：沪     3 ：浙    4 ：苏
 * 5 ：粤    6：鲁     7 ：晋    8 ：冀
 * 9 ：豫    10：川    11：渝    12：辽
 * 13：吉    14：黑    15：皖    16：鄂
 * 17：津    18：贵    19：云    20：桂
 * 21：琼    22：青    23：藏    24：蒙
 * 25：宁    26：甘    27：陕    28：闽
 * 29：赣    30：湘    31：港    32：澳
***************************************/
void put_carhead(int x, int y, int flag, int size, int color);
/*在指定位置生成一个车牌头按钮，x，y控制按钮位置，flag为车牌头代号，size控制按钮大小*/
void carhead_button(int x, int y, int flag, int size);
/*在指定位置生成一个车牌头键盘*/
void carhead_keyboard(int x, int y);
/*开机动画*/
void welcome_video(void);
/*清理主页面*/
void clear_window(int flag);
/*画一个红色的勾*/
void red_tick(int x, int y);
/*选择用户面板绘制*/
void user_select_draw(int x,int y, int sidepage);
/*选择记录面板绘制*/
void record_select_draw(int x, int y, int num);
/*高亮按钮切换函数（用户）*/
void highlight_switch_user(int unum, int sidepage);
/*高亮按钮切换函数（地点）*/
void highlight_switch_area(int i, int sidepage);
/*高亮按钮切换函数(记录)*/
void highlight_switch_record(USER user, int rnum, int sidepage);
/*高亮按钮切换函数（邮件）*/
void highlight_switch_record(USER user, int rnum, int sidepage);
/*高亮按钮切换函数(申诉)*/
void highlight_switch_appeal(USER user, int rnum, int sidepage);
/*在指定位置输出一个星期几(使用puthz函数)*/
/*flag为星期几代号，size为字号大小（可选16，24，32，48）*/
void put_week(int x, int y, int flag, int size, int color);
/*在指定位置生成一个星期几按钮，x，y控制按钮位置，flag为星期几代号，size控制按钮大小*/
void week_button(int x, int y, int flag, int size);
/*在指定位置生成一个星期键盘*/
void week_keyboard(int x, int y);
/*系统时间显示*/
void sys_time(int x, int y);
/*多行文字输出（32号字，行距为2，最大输入行数为18行）*/
void puthz_lines(int x, int y, char * str1, char * str2, char * str3, char * str4, char * str5, char * str6, char * str7, char * str8,
	 char * str9, char * str10, char * str11, char * str12, char * str13, char * str14, char * str15, char * str16, char * str17, char * str18);
#endif
