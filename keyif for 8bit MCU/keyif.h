#ifndef __KEY_IF_H__
#define __KEY_IF_H__
////////////////////////////////////////////////////////////////////////////////
typedef unsigned char   u8_t;

#define KEY_NUM_MAX     (8)

#define KEY_STA_BEGIN   (0)
#define KEY_STA_KEEP    (1)
#define KEY_STA_END     (2)

#define KEY_PERIOD_MS   (25)

void kif_Init(void);
void kif_TickHook(void);

/*
    kindex 按键索引，从0开始，而小于KEY_NUM_MAX。
    返回值：按键被按下返回非零，按键被抬起返回零。
*/
extern u8_t KeyRead(u8_t kindex);
/*
    kindex 按键索引，从0开始，而小于KEY_NUM_MAX。
    ksta   按键状态，取值为KEY_STA_系列宏。
    ktick  按键计时，以KEY_PERIOD_MS时间为计数单位。
    返回值：如果本次按键操作已经处理妥当，就返回非零。
*/
extern u8_t KeyProc(u8_t kindex, u8_t ksta, u8_t ktick);

////////////////////////////////////////////////////////////////////////////////
#endif /* __KEY_IF_H__ */

