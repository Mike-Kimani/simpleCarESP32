
//onboard led
#define ledPIN 2

//Motor driver connections
#define in1 16
#define in2 13
#define ena 15
#define lin 26
#define rin 33

//Accelerator and decelerator buttons
#define accelerator 32
#define decelerator 33

//Accelerator and decelerator
int accelerator_state = 0;
int decelerator_state = 0;
int emergency_state = 0;

//Servo pin
#define servopin 32

//Steering buttons
#define rightsteer 25
#define leftsteer 26
#define centresteer 27

//Steering button states
int rightstate;
int leftstate;
int centerstate;


//wifi credentials
const char* ssid = "mkwifi";
const char* password = "mkcart99";

//client times
uint64_t currentime;
uint64_t prevtime;
int timeoutTime;