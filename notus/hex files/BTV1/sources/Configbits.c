
// DSPIC33EP512MC806 Configuration Bit Settings

#include <p33EP512MC806.h>

 int FGS __attribute__((space(prog), address(0xF80004))) = 0xFFCF ;
//_FGS(
//    GWRP_OFF &           // General Segment Write-Protect bit (General Segment may be written)
//    GSS_OFF &            // General Segment Code-Protect bit (General Segment Code protect is disabled)
//    GSSK_OFF             // General Segment Key bits (General Segment Write Protection and Code Protection is Disabled)
//);
 int FOSCSEL __attribute__((space(prog), address(0xF80006))) = 0xFFF9 ;
//_FOSCSEL(
//    FNOSC_FRCPLL &       // Initial Oscillator Source Selection bits (Internal Fast RC with PLL (FRCPLL))
//    IESO_ON              // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)
//);
 int FOSC __attribute__((space(prog), address(0xF80008))) = 0xFFFF ;
//_FOSC(
//    POSCMD_NONE &        // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
//    OSCIOFNC_OFF &       // OSC2 Pin Function bit (OSC2 is clock output)
//    IOL1WAY_ON &         // Peripheral pin select configuration (Allow only one reconfiguration)
//    FCKSM_CSDCMD         // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)
//);
 int FWDT __attribute__((space(prog), address(0xF8000A))) = 0xFF7F ;
//_FWDT(
//    WDTPOST_PS32768 &    // Watchdog Timer Postscaler bits (1:32,768)
//    WDTPRE_PR128 &       // Watchdog Timer Prescaler bit (1:128)
//    PLLKEN_ON &          // PLL Lock Wait Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
//    WINDIS_OFF &         // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
//    FWDTEN_OFF           // Watchdog Timer Enable bit (Watchdog timer enabled/disabled by user software)
//);
 int FPOR __attribute__((space(prog), address(0xF8000C))) = 0xFFFF ;
//_FPOR(
//    FPWRT_PWR128 &       // Power-on Reset Timer Value Select bits (128ms)
//    BOREN_ON &           // Brown-out Reset (BOR) Detection Enable bit (BOR is enabled)
//    ALTI2C1_OFF          // Alternate I2C pins for I2C1 (SDA1/SCK1 pins are selected as the I/O pins for I2C1)
//);
 int FICD __attribute__((space(prog), address(0xF8000E))) = 0xFFDF ;
//_FICD(
//    ICS_PGD1 &           // ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1)
//    RSTPRI_PF &          // Reset Target Vector Select bit (Device will obtain reset instruction from Primary flash)
//    JTAGEN_OFF           // JTAG Enable bit (JTAG is disabled)
//);
 int FAS __attribute__((space(prog), address(0xF80010))) = 0xFFCF ;
//_FAS(
//    AWRP_OFF &           // Auxiliary Segment Write-protect bit (Aux Flash may be written)
//    APL_OFF &            // Auxiliary Segment Code-protect bit (Aux Flash Code protect is disabled)
//    APLK_OFF             // Auxiliary Segment Key bits (Aux Flash Write Protection and Code Protection is Disabled)
//);


