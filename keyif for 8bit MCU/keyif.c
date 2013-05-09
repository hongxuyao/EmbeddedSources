#include "keyif.h"
#include <string.h>

#if defined(KEY_NUM_MAX) && (KEY_NUM_MAX > 0)

#if KEY_NUM_MAX > 255
#error ��ģ��Ϊ8λ��Ƭ���Ż�����֧��255�����ϰ�����
#endif

static u8_t kticks[KEY_NUM_MAX];            // ÿ��������Ҫ1�ֽڼ�ʱ����
static u8_t kstats[(KEY_NUM_MAX+7)/8];      // ÿ��������Ҫ1BIT��״̬��־��
static u8_t kvalid[(KEY_NUM_MAX+7)/8];      // ÿ��������Ҫ1BIT����Ч��־��
////////////////////////////////////////////////////////////////////////////////
//|          |
//| �������� |: kif_Init
//| �������� |: 
//|          |: 
//| �����б� |: 
//|          |: 
//| ��    �� |: 
//|          |: 
//| ��ע��Ϣ |: 
//|          |: 
////////////////////////////////////////////////////////////////////////////////
void kif_Init(void)
{
    memset(kticks, 0, sizeof(kticks));
    memset(kstats, 0, sizeof(kstats));
    memset(kvalid, 0, sizeof(kvalid));
}

////////////////////////////////////////////////////////////////////////////////
//|          |
//| �������� |: kif_TickHook
//| �������� |: 
//|          |: 
//| �����б� |: 
//|          |: 
//| ��    �� |: 
//|          |: 
//| ��ע��Ϣ |: 
//|          |: 
////////////////////////////////////////////////////////////////////////////////
void kif_TickHook(void)
{
    u8_t now, msk;
    u8_t i, grp;
    
    grp = 0;
    msk = 1;
    for(i = 0; i < KEY_NUM_MAX; ++i){
        now = (KeyRead(i) ? msk : 0);
        if((kstats[grp] ^ now) & msk){
            // ����״̬�����仯��
            kstats[grp] ^= msk;
            if(now){
                // �����ձ����¡�
                kticks[i] = 0;
                kvalid[grp] |= msk;
                if(KeyProc(i, KEY_STA_BEGIN, 0)){
                    kvalid[grp] &= ~msk;
                }
            }
            else{
                // �����ձ�̧��
                kticks[i] += 1;
                KeyProc(i, KEY_STA_END, kticks[i]);
            }
        }
        else if(now){
            // �������ְ���״̬��
            kticks[i] += 1;
            if(kvalid[grp] & msk){
                // ����������Ч״̬��
                if(KeyProc(i, KEY_STA_KEEP, kticks[i])){
                    kvalid[grp] &= ~msk;
                }
            }
        }
        // �������ڼ���ִ�е��м������
        msk <<= 1;
        if(msk == 0){
            msk = 1;
            grp++;
        }
    }
}

#else /* KEY_NUM_MAX */

void kif_Init(void){ ; }
void kif_TickHook(void){ ; }

#endif /* KEY_NUM_MAX */

