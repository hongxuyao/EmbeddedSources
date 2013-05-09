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
    kindex ������������0��ʼ����С��KEY_NUM_MAX��
    ����ֵ�����������·��ط��㣬������̧�𷵻��㡣
*/
extern u8_t KeyRead(u8_t kindex);
/*
    kindex ������������0��ʼ����С��KEY_NUM_MAX��
    ksta   ����״̬��ȡֵΪKEY_STA_ϵ�кꡣ
    ktick  ������ʱ����KEY_PERIOD_MSʱ��Ϊ������λ��
    ����ֵ��������ΰ��������Ѿ������׵����ͷ��ط��㡣
*/
extern u8_t KeyProc(u8_t kindex, u8_t ksta, u8_t ktick);

////////////////////////////////////////////////////////////////////////////////
#endif /* __KEY_IF_H__ */

