
// 44, 45, 46
#define WRIST_SRV XX
#define GRIP_SRV  XX

void init_hand()
{
    analogWrite(9, 10);
    analogWrite(10, 20);
    analogWrite(44, 30);
    analogWrite(45, 100);
}
