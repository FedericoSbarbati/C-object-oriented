#include "DataSource/EventSim.h"

#include "AnalysisFramework/Event.h"
#include "AnalysisFramework/AnalysisInfo.h"
#include "AnalysisFramework/SourceFactory.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

class EventSimBuilder: public SourceFactory::AbsFactory {
 public:
  EventSimBuilder(): SourceFactory::AbsFactory( "sim" ) {}
  virtual EventSource* create( const AnalysisInfo* info ) {
    stringstream sstr;
    // get number of events to generate
    sstr.str( info->value( "sim" ) );
    unsigned int nevt;
    sstr >> nevt;
    // set seed if available
    unsigned int seed = 1;
    if ( info->contains( "seed" ) ) {
      sstr.clear();
      sstr.str( info->value( "seed" ) );
      sstr >> seed;
    }
    return new EventSim( nevt, seed );
  }
};
static EventSimBuilder es;

// simulate data with random seed
EventSim::EventSim( unsigned int n, unsigned int s ):
 nMax( n ),
 evId( 0 ) {
  srandom( s );
  pedestalMean = 12.40;
  pedestalRMS  =  1.06;
  eData.reserve( 10 );
  ElementData* ed;
  // background
  eData.push_back( ed = createElement( 0.185, 2174.56, 232.929 ) );
  ed->eMean[  0] =  0.00617186 ; ed->eRMS[  0] = 0.00283092 ;
  ed->eMean[  1] =  0.00875533 ; ed->eRMS[  1] = 0.00371295 ;
  ed->eMean[  2] =  0.0111021  ; ed->eRMS[  2] = 0.00420107 ;
  ed->eMean[  3] =  0.0141192  ; ed->eRMS[  3] = 0.00428146 ;
  ed->eMean[  4] =  0.0160548  ; ed->eRMS[  4] = 0.00454323 ;
  ed->eMean[  5] =  0.0204227  ; ed->eRMS[  5] = 0.00384439 ;
  ed->eMean[  6] =  0.0248287  ; ed->eRMS[  6] = 0.00402712 ;
  ed->eMean[  7] =  0.0277417  ; ed->eRMS[  7] = 0.00382134 ;
  ed->eMean[  8] =  0.0312791  ; ed->eRMS[  8] = 0.00385286 ;
  ed->eMean[  9] =  0.0352681  ; ed->eRMS[  9] = 0.00427314 ;
  ed->eMean[ 10] =  0.0382166  ; ed->eRMS[ 10] = 0.00420217 ;
  ed->eMean[ 11] =  0.0408477  ; ed->eRMS[ 11] = 0.00434335 ;
  ed->eMean[ 12] =  0.0426525  ; ed->eRMS[ 12] = 0.00536044 ;
  ed->eMean[ 13] =  0.0455428  ; ed->eRMS[ 13] = 0.00582643 ;
  ed->eMean[ 14] =  0.0463118  ; ed->eRMS[ 14] = 0.0066224  ;
  ed->eMean[ 15] =  0.047383   ; ed->eRMS[ 15] = 0.00613224 ;
  ed->eMean[ 16] =  0.0478248  ; ed->eRMS[ 16] = 0.00788236 ;
  ed->eMean[ 17] =  0.0467512  ; ed->eRMS[ 17] = 0.00799372 ;
  ed->eMean[ 18] =  0.0467323  ; ed->eRMS[ 18] = 0.00876391 ;
  ed->eMean[ 19] =  0.0437496  ; ed->eRMS[ 19] = 0.00823547 ;
  ed->eMean[ 20] =  0.0399369  ; ed->eRMS[ 20] = 0.00895314 ;
  ed->eMean[ 21] =  0.0398118  ; ed->eRMS[ 21] = 0.00874853 ;
  ed->eMean[ 22] =  0.037366   ; ed->eRMS[ 22] = 0.00782153 ;
  ed->eMean[ 23] =  0.0320156  ; ed->eRMS[ 23] = 0.00854819 ;
  ed->eMean[ 24] =  0.0287915  ; ed->eRMS[ 24] = 0.00872341 ;
  ed->eMean[ 25] =  0.026506   ; ed->eRMS[ 25] = 0.00745832 ;
  ed->eMean[ 26] =  0.0223559  ; ed->eRMS[ 26] = 0.00614255 ;
  ed->eMean[ 27] =  0.0216162  ; ed->eRMS[ 27] = 0.00656849 ;
  ed->eMean[ 28] =  0.0187063  ; ed->eRMS[ 28] = 0.00474834 ;
  ed->eMean[ 29] =  0.0140783  ; ed->eRMS[ 29] = 0.00541854 ;
  ed->eMean[ 30] =  0.0132844  ; ed->eRMS[ 30] = 0.00516788 ;
  ed->eMean[ 31] =  0.0101448  ; ed->eRMS[ 31] = 0.00455909 ;
  ed->eMean[ 32] =  0.00925454 ; ed->eRMS[ 32] = 0.00337192 ;
  ed->eMean[ 33] =  0.00658689 ; ed->eRMS[ 33] = 0.0031411  ;
  ed->eMean[ 34] =  0.00619813 ; ed->eRMS[ 34] = 0.00312708 ;
  ed->eMean[ 35] =  0.00461658 ; ed->eRMS[ 35] = 0.00191922 ;
  ed->eMean[ 36] =  0.00356906 ; ed->eRMS[ 36] = 0.00174911 ;
  ed->eMean[ 37] =  0.00295115 ; ed->eRMS[ 37] = 0.00157353 ;
  ed->eMean[ 38] =  0.00246556 ; ed->eRMS[ 38] = 0.00112288 ;
  ed->eMean[ 39] =  0.00214028 ; ed->eRMS[ 39] = 0.00110981 ;
  ed->eMean[ 40] =  0.00163179 ; ed->eRMS[ 40] = 0.000771388;
  ed->eMean[ 41] =  0.00144608 ; ed->eRMS[ 41] = 0.00069292 ;
  ed->eMean[ 42] =  0.0010238  ; ed->eRMS[ 42] = 0.000691586;
  ed->eMean[ 43] =  0.00104668 ; ed->eRMS[ 43] = 0.000603828;
  ed->eMean[ 44] =  0.00101808 ; ed->eRMS[ 44] = 0.000539497;
  ed->eMean[ 45] =  0.000781447; ed->eRMS[ 45] = 0.000527251;
  ed->eMean[ 46] =  0.000706962; ed->eRMS[ 46] = 0.000554239;
  ed->eMean[ 47] =  0.000705078; ed->eRMS[ 47] = 0.00053498 ;
  ed->eMean[ 48] =  0.000500964; ed->eRMS[ 48] = 0.000600691;
  ed->eMean[ 49] =  0.000552039; ed->eRMS[ 49] = 0.000523923;
  ed->eMean[ 50] =  0.000492345; ed->eRMS[ 50] = 0.000467295;
  ed->eMean[ 51] =  0.000546823; ed->eRMS[ 51] = 0.000472344;
  ed->eMean[ 52] =  0.00031415 ; ed->eRMS[ 52] = 0.000441172;
  ed->eMean[ 53] =  0.000449701; ed->eRMS[ 53] = 0.000470907;
  ed->eMean[ 54] =  0.000434586; ed->eRMS[ 54] = 0.00044366 ;
  ed->eMean[ 55] =  0.000272917; ed->eRMS[ 55] = 0.000411164;
  ed->eMean[ 56] =  0.000378084; ed->eRMS[ 56] = 0.000452646;
  ed->eMean[ 57] =  0.000181915; ed->eRMS[ 57] = 0.000415722;
  ed->eMean[ 58] =  0.000256609; ed->eRMS[ 58] = 0.00044672 ;
  ed->eMean[ 59] =  0.000318352; ed->eRMS[ 59] = 0.000494092;
  ed->eMean[ 60] =  0.000258261; ed->eRMS[ 60] = 0.000429734;
  ed->eMean[ 61] =  0.000217641; ed->eRMS[ 61] = 0.000511202;
  ed->eMean[ 62] =  0.000167852; ed->eRMS[ 62] = 0.000493463;
  ed->eMean[ 63] =  0.000252701; ed->eRMS[ 63] = 0.00054829 ;
  ed->eMean[ 64] =  0.000243635; ed->eRMS[ 64] = 0.000420378;
  ed->eMean[ 65] =  0.000182873; ed->eRMS[ 65] = 0.000405767;
  ed->eMean[ 66] =  5.51188e-05; ed->eRMS[ 66] = 0.000452999;
  ed->eMean[ 67] =  9.57319e-05; ed->eRMS[ 67] = 0.000457367;
  ed->eMean[ 68] =  2.04019e-05; ed->eRMS[ 68] = 0.000525172;
  ed->eMean[ 69] =  9.87388e-05; ed->eRMS[ 69] = 0.000422639;
  ed->eMean[ 70] =  3.95379e-05; ed->eRMS[ 70] = 0.00044192 ;
  ed->eMean[ 71] = -4.17495e-05; ed->eRMS[ 71] = 0.000426331;
  ed->eMean[ 72] =  3.49877e-05; ed->eRMS[ 72] = 0.000436585;
  ed->eMean[ 73] = -5.17062e-05; ed->eRMS[ 73] = 0.000466342;
  ed->eMean[ 74] =  0.000151283; ed->eRMS[ 74] = 0.000452096;
  ed->eMean[ 75] =  3.01041e-05; ed->eRMS[ 75] = 0.000426755;
  ed->eMean[ 76] =  8.63322e-05; ed->eRMS[ 76] = 0.000477502;
  ed->eMean[ 77] = -4.38748e-05; ed->eRMS[ 77] = 0.000532961;
  ed->eMean[ 78] =  9.6277e-06 ; ed->eRMS[ 78] = 0.000474306;
  ed->eMean[ 79] =  7.1011e-05 ; ed->eRMS[ 79] = 0.000528368;
  ed->eMean[ 80] =  4.97606e-05; ed->eRMS[ 80] = 0.00043765 ;
  ed->eMean[ 81] =  0.000123459; ed->eRMS[ 81] = 0.000488096;
  ed->eMean[ 82] =  5.96278e-05; ed->eRMS[ 82] = 0.000457552;
  ed->eMean[ 83] = -4.18995e-06; ed->eRMS[ 83] = 0.000450087;
  ed->eMean[ 84] =  2.71664e-05; ed->eRMS[ 84] = 0.000476952;
  ed->eMean[ 85] =  0.000109396; ed->eRMS[ 85] = 0.000470178;
  ed->eMean[ 86] =  0.000104366; ed->eRMS[ 86] = 0.000392844;
  ed->eMean[ 87] =  3.66557e-05; ed->eRMS[ 87] = 0.000398362;
  ed->eMean[ 88] =  5.16758e-05; ed->eRMS[ 88] = 0.000465033;
  ed->eMean[ 89] =  0.000100368; ed->eRMS[ 89] = 0.000448755;
  ed->eMean[ 90] =  0.000130473; ed->eRMS[ 90] = 0.000411379;
  ed->eMean[ 91] =  0.000140466; ed->eRMS[ 91] = 0.000442432;
  ed->eMean[ 92] =  4.23742e-05; ed->eRMS[ 92] = 0.000504713;
  ed->eMean[ 93] = -3.79935e-05; ed->eRMS[ 93] = 0.000409066;
  ed->eMean[ 94] = -5.49608e-05; ed->eRMS[ 94] = 0.000437502;
  ed->eMean[ 95] =  1.05524e-05; ed->eRMS[ 95] = 0.000450422;
  ed->eMean[ 96] =  8.14043e-05; ed->eRMS[ 96] = 0.000472509;
  ed->eMean[ 97] = -7.57538e-06; ed->eRMS[ 97] = 0.000413005;
  ed->eMean[ 98] =  1.40212e-06; ed->eRMS[ 98] = 0.0005167  ;
  ed->eMean[ 99] = -2.90837e-05; ed->eRMS[ 99] = 0.000458408;
  ed->eMean[100] =  2.31123e-05; ed->eRMS[100] = 0.000484358;
  ed->eMean[101] = -3.97647e-05; ed->eRMS[101] = 0.000472613;
  ed->eMean[102] = -5.9917e-05 ; ed->eRMS[102] = 0.000431351;
  ed->eMean[103] =  0.000110812; ed->eRMS[103] = 0.000390313;
  ed->eMean[104] = -2.98283e-06; ed->eRMS[104] = 0.000480609;
  ed->eMean[105] = -9.54238e-05; ed->eRMS[105] = 0.000364773;
  ed->eMean[106] =  7.20788e-05; ed->eRMS[106] = 0.000395088;
  ed->eMean[107] =  5.48455e-05; ed->eRMS[107] = 0.000518217;
  ed->eMean[108] =  1.26177e-06; ed->eRMS[108] = 0.000444375;
  ed->eMean[109] =  4.52217e-06; ed->eRMS[109] = 0.000523545;
  ed->eMean[110] = -0.000129504; ed->eRMS[110] = 0.000489021;
  ed->eMean[111] =  5.3976e-05 ; ed->eRMS[111] = 0.000551371;
  ed->eMean[112] = -1.77791e-05; ed->eRMS[112] = 0.000497577;
  ed->eMean[113] = -7.00009e-05; ed->eRMS[113] = 0.0004771  ;
  ed->eMean[114] = -3.6999e-05 ; ed->eRMS[114] = 0.000502025;
  ed->eMean[115] =  3.80028e-05; ed->eRMS[115] = 0.00055892 ;
  ed->eMean[116] =  3.1181e-06 ; ed->eRMS[116] = 0.000494693;
  ed->eMean[117] = -5.58138e-05; ed->eRMS[117] = 0.000554724;
  ed->eMean[118] =  1.44678e-05; ed->eRMS[118] = 0.000453707;
  ed->eMean[119] =  0.000106088; ed->eRMS[119] = 0.000436416;
  // barberium
  eData.push_back( ed = createElement( 0.331, 4824.65, 41.1096 ) );
  ed->eMean[  0] =  0.000739383; ed->eRMS[  0] = 0.000223011;
  ed->eMean[  1] =  0.00141051 ; ed->eRMS[  1] = 0.000272632;
  ed->eMean[  2] =  0.00224439 ; ed->eRMS[  2] = 0.000311208;
  ed->eMean[  3] =  0.00378134 ; ed->eRMS[  3] = 0.000367513;
  ed->eMean[  4] =  0.00577057 ; ed->eRMS[  4] = 0.000510939;
  ed->eMean[  5] =  0.0082949  ; ed->eRMS[  5] = 0.000574824;
  ed->eMean[  6] =  0.0112423  ; ed->eRMS[  6] = 0.000700195;
  ed->eMean[  7] =  0.0143544  ; ed->eRMS[  7] = 0.00066931 ;
  ed->eMean[  8] =  0.0176696  ; ed->eRMS[  8] = 0.000698172;
  ed->eMean[  9] =  0.0208622  ; ed->eRMS[  9] = 0.000740344;
  ed->eMean[ 10] =  0.0242055  ; ed->eRMS[ 10] = 0.000653528;
  ed->eMean[ 11] =  0.0269691  ; ed->eRMS[ 11] = 0.000592436;
  ed->eMean[ 12] =  0.0294304  ; ed->eRMS[ 12] = 0.000613204;
  ed->eMean[ 13] =  0.0316201  ; ed->eRMS[ 13] = 0.000591498;
  ed->eMean[ 14] =  0.0334212  ; ed->eRMS[ 14] = 0.000464906;
  ed->eMean[ 15] =  0.0347932  ; ed->eRMS[ 15] = 0.000510619;
  ed->eMean[ 16] =  0.0356387  ; ed->eRMS[ 16] = 0.000496147;
  ed->eMean[ 17] =  0.0361165  ; ed->eRMS[ 17] = 0.000452864;
  ed->eMean[ 18] =  0.0363311  ; ed->eRMS[ 18] = 0.000437419;
  ed->eMean[ 19] =  0.0362745  ; ed->eRMS[ 19] = 0.00045895 ;
  ed->eMean[ 20] =  0.0358892  ; ed->eRMS[ 20] = 0.000420162;
  ed->eMean[ 21] =  0.0353083  ; ed->eRMS[ 21] = 0.000424986;
  ed->eMean[ 22] =  0.0347484  ; ed->eRMS[ 22] = 0.000486221;
  ed->eMean[ 23] =  0.033882   ; ed->eRMS[ 23] = 0.000515341;
  ed->eMean[ 24] =  0.0332011  ; ed->eRMS[ 24] = 0.000548802;
  ed->eMean[ 25] =  0.0323076  ; ed->eRMS[ 25] = 0.000527767;
  ed->eMean[ 26] =  0.0314949  ; ed->eRMS[ 26] = 0.000531577;
  ed->eMean[ 27] =  0.0304583  ; ed->eRMS[ 27] = 0.000533424;
  ed->eMean[ 28] =  0.029441   ; ed->eRMS[ 28] = 0.000539384;
  ed->eMean[ 29] =  0.0283201  ; ed->eRMS[ 29] = 0.000615089;
  ed->eMean[ 30] =  0.0270705  ; ed->eRMS[ 30] = 0.000573214;
  ed->eMean[ 31] =  0.0256997  ; ed->eRMS[ 31] = 0.000501666;
  ed->eMean[ 32] =  0.0243413  ; ed->eRMS[ 32] = 0.000593877;
  ed->eMean[ 33] =  0.022493   ; ed->eRMS[ 33] = 0.000681396;
  ed->eMean[ 34] =  0.020566   ; ed->eRMS[ 34] = 0.000702861;
  ed->eMean[ 35] =  0.0187036  ; ed->eRMS[ 35] = 0.000647843;
  ed->eMean[ 36] =  0.0169248  ; ed->eRMS[ 36] = 0.000651385;
  ed->eMean[ 37] =  0.0150982  ; ed->eRMS[ 37] = 0.000682919;
  ed->eMean[ 38] =  0.0132109  ; ed->eRMS[ 38] = 0.000698832;
  ed->eMean[ 39] =  0.0114752  ; ed->eRMS[ 39] = 0.00066011 ;
  ed->eMean[ 40] =  0.00991342 ; ed->eRMS[ 40] = 0.000577615;
  ed->eMean[ 41] =  0.00837494 ; ed->eRMS[ 41] = 0.000508058;
  ed->eMean[ 42] =  0.00717823 ; ed->eRMS[ 42] = 0.000515602;
  ed->eMean[ 43] =  0.00603144 ; ed->eRMS[ 43] = 0.000482644;
  ed->eMean[ 44] =  0.00492134 ; ed->eRMS[ 44] = 0.000393144;
  ed->eMean[ 45] =  0.00405105 ; ed->eRMS[ 45] = 0.000398762;
  ed->eMean[ 46] =  0.00337541 ; ed->eRMS[ 46] = 0.000335567;
  ed->eMean[ 47] =  0.0027599  ; ed->eRMS[ 47] = 0.000344101;
  ed->eMean[ 48] =  0.00222337 ; ed->eRMS[ 48] = 0.000309705;
  ed->eMean[ 49] =  0.00182817 ; ed->eRMS[ 49] = 0.000284485;
  ed->eMean[ 50] =  0.0015239  ; ed->eRMS[ 50] = 0.00025411 ;
  ed->eMean[ 51] =  0.00133034 ; ed->eRMS[ 51] = 0.000243506;
  ed->eMean[ 52] =  0.00104053 ; ed->eRMS[ 52] = 0.000231567;
  ed->eMean[ 53] =  0.000882567; ed->eRMS[ 53] = 0.000230389;
  ed->eMean[ 54] =  0.000764895; ed->eRMS[ 54] = 0.000217539;
  ed->eMean[ 55] =  0.000727742; ed->eRMS[ 55] = 0.000193926;
  ed->eMean[ 56] =  0.000638909; ed->eRMS[ 56] = 0.000200782;
  ed->eMean[ 57] =  0.000577079; ed->eRMS[ 57] = 0.000201902;
  ed->eMean[ 58] =  0.000539629; ed->eRMS[ 58] = 0.000208024;
  ed->eMean[ 59] =  0.000470049; ed->eRMS[ 59] = 0.000221913;
  ed->eMean[ 60] =  0.000432177; ed->eRMS[ 60] = 0.00021761 ;
  ed->eMean[ 61] =  0.000427488; ed->eRMS[ 61] = 0.000245482;
  ed->eMean[ 62] =  0.000392217; ed->eRMS[ 62] = 0.000213509;
  ed->eMean[ 63] =  0.000374798; ed->eRMS[ 63] = 0.000219085;
  ed->eMean[ 64] =  0.000363478; ed->eRMS[ 64] = 0.000239767;
  ed->eMean[ 65] =  0.000273289; ed->eRMS[ 65] = 0.000233558;
  ed->eMean[ 66] =  0.000293484; ed->eRMS[ 66] = 0.000211937;
  ed->eMean[ 67] =  0.00029709 ; ed->eRMS[ 67] = 0.000225403;
  ed->eMean[ 68] =  0.000290725; ed->eRMS[ 68] = 0.000218445;
  ed->eMean[ 69] =  0.000237564; ed->eRMS[ 69] = 0.00023639 ;
  ed->eMean[ 70] =  0.000189386; ed->eRMS[ 70] = 0.000238074;
  ed->eMean[ 71] =  0.000226496; ed->eRMS[ 71] = 0.000227537;
  ed->eMean[ 72] =  0.000176241; ed->eRMS[ 72] = 0.000226643;
  ed->eMean[ 73] =  0.000178899; ed->eRMS[ 73] = 0.000227971;
  ed->eMean[ 74] =  0.000163724; ed->eRMS[ 74] = 0.00023599 ;
  ed->eMean[ 75] =  0.000147449; ed->eRMS[ 75] = 0.000215707;
  ed->eMean[ 76] =  0.000164244; ed->eRMS[ 76] = 0.000225418;
  ed->eMean[ 77] =  0.00016311 ; ed->eRMS[ 77] = 0.000202143;
  ed->eMean[ 78] =  0.000118606; ed->eRMS[ 78] = 0.000209573;
  ed->eMean[ 79] =  0.000134256; ed->eRMS[ 79] = 0.000191583;
  ed->eMean[ 80] =  0.000133056; ed->eRMS[ 80] = 0.000225888;
  ed->eMean[ 81] =  0.000116156; ed->eRMS[ 81] = 0.000204639;
  ed->eMean[ 82] =  0.000100659; ed->eRMS[ 82] = 0.000211188;
  ed->eMean[ 83] =  0.000124432; ed->eRMS[ 83] = 0.000210667;
  ed->eMean[ 84] =  0.000155758; ed->eRMS[ 84] = 0.000217307;
  ed->eMean[ 85] =  0.000142592; ed->eRMS[ 85] = 0.000188213;
  ed->eMean[ 86] =  9.42585e-05; ed->eRMS[ 86] = 0.000225377;
  ed->eMean[ 87] =  0.000145681; ed->eRMS[ 87] = 0.000213949;
  ed->eMean[ 88] =  0.000141788; ed->eRMS[ 88] = 0.000222977;
  ed->eMean[ 89] =  0.000123028; ed->eRMS[ 89] = 0.000184981;
  ed->eMean[ 90] =  0.000143175; ed->eRMS[ 90] = 0.000215405;
  ed->eMean[ 91] =  0.00011187 ; ed->eRMS[ 91] = 0.000204134;
  ed->eMean[ 92] =  9.67266e-05; ed->eRMS[ 92] = 0.000234011;
  ed->eMean[ 93] =  0.000121234; ed->eRMS[ 93] = 0.000228094;
  ed->eMean[ 94] =  0.000105459; ed->eRMS[ 94] = 0.000212049;
  ed->eMean[ 95] =  0.000122917; ed->eRMS[ 95] = 0.000205176;
  ed->eMean[ 96] =  0.000149883; ed->eRMS[ 96] = 0.000221557;
  ed->eMean[ 97] =  0.000170736; ed->eRMS[ 97] = 0.000202817;
  ed->eMean[ 98] =  0.000133101; ed->eRMS[ 98] = 0.000225345;
  ed->eMean[ 99] =  9.1155e-05 ; ed->eRMS[ 99] = 0.000232675;
  ed->eMean[100] =  0.00012623 ; ed->eRMS[100] = 0.000217593;
  ed->eMean[101] =  8.55312e-05; ed->eRMS[101] = 0.00020194 ;
  ed->eMean[102] =  0.000126217; ed->eRMS[102] = 0.000195572;
  ed->eMean[103] =  0.000132375; ed->eRMS[103] = 0.000194648;
  ed->eMean[104] =  9.04247e-05; ed->eRMS[104] = 0.000211399;
  ed->eMean[105] =  0.000101872; ed->eRMS[105] = 0.000222616;
  ed->eMean[106] =  9.66812e-05; ed->eRMS[106] = 0.000227473;
  ed->eMean[107] =  0.000108692; ed->eRMS[107] = 0.000222351;
  ed->eMean[108] =  9.23423e-05; ed->eRMS[108] = 0.000218505;
  ed->eMean[109] =  6.49457e-05; ed->eRMS[109] = 0.00021185 ;
  ed->eMean[110] =  6.56411e-05; ed->eRMS[110] = 0.000189741;
  ed->eMean[111] =  6.36356e-05; ed->eRMS[111] = 0.000210535;
  ed->eMean[112] =  3.97531e-05; ed->eRMS[112] = 0.000216542;
  ed->eMean[113] =  5.67837e-05; ed->eRMS[113] = 0.000210313;
  ed->eMean[114] =  3.16262e-05; ed->eRMS[114] = 0.000180789;
  ed->eMean[115] =  4.90329e-05; ed->eRMS[115] = 0.000194635;
  ed->eMean[116] =  9.85605e-07; ed->eRMS[116] = 0.000226144;
  ed->eMean[117] =  3.09095e-05; ed->eRMS[117] = 0.000216102;
  ed->eMean[118] =  2.73933e-05; ed->eRMS[118] = 0.000202152;
  ed->eMean[119] =  8.16603e-05; ed->eRMS[119] = 0.000208207;
  // cabernetium
  eData.push_back( ed = createElement( 0.205, 5133.36, 38.7556 ) );
  ed->eMean[  0] =  0.000731875; ed->eRMS[  0] = 0.000216174;
  ed->eMean[  1] =  0.00131136 ; ed->eRMS[  1] = 0.000200953;
  ed->eMean[  2] =  0.00209722 ; ed->eRMS[  2] = 0.000301233;
  ed->eMean[  3] =  0.00352131 ; ed->eRMS[  3] = 0.000407611;
  ed->eMean[  4] =  0.00551148 ; ed->eRMS[  4] = 0.000470327;
  ed->eMean[  5] =  0.00766178 ; ed->eRMS[  5] = 0.00053827 ;
  ed->eMean[  6] =  0.0104413  ; ed->eRMS[  6] = 0.000542537;
  ed->eMean[  7] =  0.0134691  ; ed->eRMS[  7] = 0.000713612;
  ed->eMean[  8] =  0.0165808  ; ed->eRMS[  8] = 0.000625484;
  ed->eMean[  9] =  0.0194862  ; ed->eRMS[  9] = 0.000624061;
  ed->eMean[ 10] =  0.0227197  ; ed->eRMS[ 10] = 0.000530693;
  ed->eMean[ 11] =  0.0251269  ; ed->eRMS[ 11] = 0.000612895;
  ed->eMean[ 12] =  0.0275158  ; ed->eRMS[ 12] = 0.000588536;
  ed->eMean[ 13] =  0.0296223  ; ed->eRMS[ 13] = 0.000459093;
  ed->eMean[ 14] =  0.0313717  ; ed->eRMS[ 14] = 0.000470877;
  ed->eMean[ 15] =  0.0326393  ; ed->eRMS[ 15] = 0.000430182;
  ed->eMean[ 16] =  0.0334994  ; ed->eRMS[ 16] = 0.000400838;
  ed->eMean[ 17] =  0.0340638  ; ed->eRMS[ 17] = 0.000410878;
  ed->eMean[ 18] =  0.0344259  ; ed->eRMS[ 18] = 0.000428971;
  ed->eMean[ 19] =  0.0342918  ; ed->eRMS[ 19] = 0.000433768;
  ed->eMean[ 20] =  0.0338171  ; ed->eRMS[ 20] = 0.000429535;
  ed->eMean[ 21] =  0.0333907  ; ed->eRMS[ 21] = 0.000410091;
  ed->eMean[ 22] =  0.0328789  ; ed->eRMS[ 22] = 0.000449369;
  ed->eMean[ 23] =  0.0320915  ; ed->eRMS[ 23] = 0.000465151;
  ed->eMean[ 24] =  0.0313039  ; ed->eRMS[ 24] = 0.000431576;
  ed->eMean[ 25] =  0.0304875  ; ed->eRMS[ 25] = 0.000400982;
  ed->eMean[ 26] =  0.029705   ; ed->eRMS[ 26] = 0.000448417;
  ed->eMean[ 27] =  0.0289852  ; ed->eRMS[ 27] = 0.000424832;
  ed->eMean[ 28] =  0.0281325  ; ed->eRMS[ 28] = 0.000430881;
  ed->eMean[ 29] =  0.0274096  ; ed->eRMS[ 29] = 0.000390797;
  ed->eMean[ 30] =  0.0265035  ; ed->eRMS[ 30] = 0.000481592;
  ed->eMean[ 31] =  0.0255825  ; ed->eRMS[ 31] = 0.00048941 ;
  ed->eMean[ 32] =  0.0246601  ; ed->eRMS[ 32] = 0.000420232;
  ed->eMean[ 33] =  0.0236825  ; ed->eRMS[ 33] = 0.000450495;
  ed->eMean[ 34] =  0.0225795  ; ed->eRMS[ 34] = 0.000483932;
  ed->eMean[ 35] =  0.0209978  ; ed->eRMS[ 35] = 0.000575415;
  ed->eMean[ 36] =  0.0194982  ; ed->eRMS[ 36] = 0.000626476;
  ed->eMean[ 37] =  0.0178351  ; ed->eRMS[ 37] = 0.000549799;
  ed->eMean[ 38] =  0.016237   ; ed->eRMS[ 38] = 0.000551284;
  ed->eMean[ 39] =  0.0145388  ; ed->eRMS[ 39] = 0.000541549;
  ed->eMean[ 40] =  0.0127853  ; ed->eRMS[ 40] = 0.000510416;
  ed->eMean[ 41] =  0.011352   ; ed->eRMS[ 41] = 0.000481397;
  ed->eMean[ 42] =  0.00995455 ; ed->eRMS[ 42] = 0.000532224;
  ed->eMean[ 43] =  0.00836832 ; ed->eRMS[ 43] = 0.000484863;
  ed->eMean[ 44] =  0.00732856 ; ed->eRMS[ 44] = 0.00041728 ;
  ed->eMean[ 45] =  0.00593388 ; ed->eRMS[ 45] = 0.000385107;
  ed->eMean[ 46] =  0.00510795 ; ed->eRMS[ 46] = 0.00036758 ;
  ed->eMean[ 47] =  0.00411593 ; ed->eRMS[ 47] = 0.000348294;
  ed->eMean[ 48] =  0.00360421 ; ed->eRMS[ 48] = 0.000278411;
  ed->eMean[ 49] =  0.00286728 ; ed->eRMS[ 49] = 0.000267703;
  ed->eMean[ 50] =  0.00239901 ; ed->eRMS[ 50] = 0.000247109;
  ed->eMean[ 51] =  0.00195791 ; ed->eRMS[ 51] = 0.000252371;
  ed->eMean[ 52] =  0.00163043 ; ed->eRMS[ 52] = 0.000232484;
  ed->eMean[ 53] =  0.00133712 ; ed->eRMS[ 53] = 0.000217866;
  ed->eMean[ 54] =  0.00111379 ; ed->eRMS[ 54] = 0.000230707;
  ed->eMean[ 55] =  0.0010001  ; ed->eRMS[ 55] = 0.000184561;
  ed->eMean[ 56] =  0.000823642; ed->eRMS[ 56] = 0.000217804;
  ed->eMean[ 57] =  0.000770128; ed->eRMS[ 57] = 0.000193474;
  ed->eMean[ 58] =  0.000665029; ed->eRMS[ 58] = 0.000208588;
  ed->eMean[ 59] =  0.000591424; ed->eRMS[ 59] = 0.000233859;
  ed->eMean[ 60] =  0.00054081 ; ed->eRMS[ 60] = 0.000180594;
  ed->eMean[ 61] =  0.000492939; ed->eRMS[ 61] = 0.000176802;
  ed->eMean[ 62] =  0.000451148; ed->eRMS[ 62] = 0.000203907;
  ed->eMean[ 63] =  0.000430074; ed->eRMS[ 63] = 0.000201683;
  ed->eMean[ 64] =  0.000379367; ed->eRMS[ 64] = 0.000202226;
  ed->eMean[ 65] =  0.000366155; ed->eRMS[ 65] = 0.000188894;
  ed->eMean[ 66] =  0.000313599; ed->eRMS[ 66] = 0.000176839;
  ed->eMean[ 67] =  0.000314302; ed->eRMS[ 67] = 0.00020864 ;
  ed->eMean[ 68] =  0.000323192; ed->eRMS[ 68] = 0.00018162 ;
  ed->eMean[ 69] =  0.000272303; ed->eRMS[ 69] = 0.000191782;
  ed->eMean[ 70] =  0.000250651; ed->eRMS[ 70] = 0.00016033 ;
  ed->eMean[ 71] =  0.000248531; ed->eRMS[ 71] = 0.000175822;
  ed->eMean[ 72] =  0.000213277; ed->eRMS[ 72] = 0.000185523;
  ed->eMean[ 73] =  0.000206602; ed->eRMS[ 73] = 0.000189685;
  ed->eMean[ 74] =  0.000215335; ed->eRMS[ 74] = 0.000195234;
  ed->eMean[ 75] =  0.000244108; ed->eRMS[ 75] = 0.00019711 ;
  ed->eMean[ 76] =  0.000174118; ed->eRMS[ 76] = 0.000174716;
  ed->eMean[ 77] =  0.000190386; ed->eRMS[ 77] = 0.000185807;
  ed->eMean[ 78] =  0.000151245; ed->eRMS[ 78] = 0.000175611;
  ed->eMean[ 79] =  0.000127395; ed->eRMS[ 79] = 0.0001407  ;
  ed->eMean[ 80] =  0.000173102; ed->eRMS[ 80] = 0.000195644;
  ed->eMean[ 81] =  0.00016251 ; ed->eRMS[ 81] = 0.000186223;
  ed->eMean[ 82] =  0.000107297; ed->eRMS[ 82] = 0.000195712;
  ed->eMean[ 83] =  0.000114075; ed->eRMS[ 83] = 0.00018022 ;
  ed->eMean[ 84] =  8.9981e-05 ; ed->eRMS[ 84] = 0.000206936;
  ed->eMean[ 85] =  0.000124591; ed->eRMS[ 85] = 0.000197328;
  ed->eMean[ 86] =  8.42933e-05; ed->eRMS[ 86] = 0.000193073;
  ed->eMean[ 87] =  0.0001274  ; ed->eRMS[ 87] = 0.000204247;
  ed->eMean[ 88] =  8.63442e-05; ed->eRMS[ 88] = 0.000186206;
  ed->eMean[ 89] =  0.000133278; ed->eRMS[ 89] = 0.000202166;
  ed->eMean[ 90] =  0.000128105; ed->eRMS[ 90] = 0.000189498;
  ed->eMean[ 91] =  0.000129151; ed->eRMS[ 91] = 0.000160112;
  ed->eMean[ 92] =  0.000115976; ed->eRMS[ 92] = 0.000178448;
  ed->eMean[ 93] =  9.20512e-05; ed->eRMS[ 93] = 0.0002114  ;
  ed->eMean[ 94] =  9.00317e-05; ed->eRMS[ 94] = 0.00020677 ;
  ed->eMean[ 95] =  6.83141e-05; ed->eRMS[ 95] = 0.000192071;
  ed->eMean[ 96] =  0.000103496; ed->eRMS[ 96] = 0.000188764;
  ed->eMean[ 97] =  8.33365e-05; ed->eRMS[ 97] = 0.000190312;
  ed->eMean[ 98] =  0.000114814; ed->eRMS[ 98] = 0.000193603;
  ed->eMean[ 99] =  0.000125484; ed->eRMS[ 99] = 0.000206263;
  ed->eMean[100] =  3.85579e-05; ed->eRMS[100] = 0.000189642;
  ed->eMean[101] =  8.62313e-05; ed->eRMS[101] = 0.000208334;
  ed->eMean[102] =  0.000110229; ed->eRMS[102] = 0.000205213;
  ed->eMean[103] =  8.44394e-05; ed->eRMS[103] = 0.000176703;
  ed->eMean[104] =  7.75904e-05; ed->eRMS[104] = 0.00019423 ;
  ed->eMean[105] =  4.34432e-05; ed->eRMS[105] = 0.000179891;
  ed->eMean[106] =  7.00999e-05; ed->eRMS[106] = 0.000166742;
  ed->eMean[107] =  8.62854e-05; ed->eRMS[107] = 0.000192462;
  ed->eMean[108] =  8.34484e-05; ed->eRMS[108] = 0.000192612;
  ed->eMean[109] =  0.000128276; ed->eRMS[109] = 0.000171021;
  ed->eMean[110] =  9.77557e-05; ed->eRMS[110] = 0.000182945;
  ed->eMean[111] =  9.77061e-05; ed->eRMS[111] = 0.000190885;
  ed->eMean[112] =  7.31124e-05; ed->eRMS[112] = 0.000194719;
  ed->eMean[113] =  0.000117944; ed->eRMS[113] = 0.000171027;
  ed->eMean[114] =  0.000129382; ed->eRMS[114] = 0.000204295;
  ed->eMean[115] =  0.000124551; ed->eRMS[115] = 0.000176565;
  ed->eMean[116] =  8.35328e-05; ed->eRMS[116] = 0.000175368;
  ed->eMean[117] =  6.80661e-05; ed->eRMS[117] = 0.000192152;
  ed->eMean[118] =  8.63691e-05; ed->eRMS[118] = 0.000211825;
  ed->eMean[119] =  3.94968e-05; ed->eRMS[119] = 0.000184612;
  // amaronium
  eData.push_back( ed = createElement( 0.279, 5430.18, 45.9783 ) );
  ed->eMean[  0] =  0.000566673; ed->eRMS[  0] = 0.000222782;
  ed->eMean[  1] =  0.00111811 ; ed->eRMS[  1] = 0.00026317 ;
  ed->eMean[  2] =  0.00195405 ; ed->eRMS[  2] = 0.000312823;
  ed->eMean[  3] =  0.00325494 ; ed->eRMS[  3] = 0.000381154;
  ed->eMean[  4] =  0.005025   ; ed->eRMS[  4] = 0.000423513;
  ed->eMean[  5] =  0.00740256 ; ed->eRMS[  5] = 0.000565286;
  ed->eMean[  6] =  0.0100486  ; ed->eRMS[  6] = 0.000540143;
  ed->eMean[  7] =  0.0128893  ; ed->eRMS[  7] = 0.000671797;
  ed->eMean[  8] =  0.0155269  ; ed->eRMS[  8] = 0.000638195;
  ed->eMean[  9] =  0.0187442  ; ed->eRMS[  9] = 0.000589522;
  ed->eMean[ 10] =  0.021468   ; ed->eRMS[ 10] = 0.00057089 ;
  ed->eMean[ 11] =  0.023856   ; ed->eRMS[ 11] = 0.000533518;
  ed->eMean[ 12] =  0.0262593  ; ed->eRMS[ 12] = 0.000532963;
  ed->eMean[ 13] =  0.0281866  ; ed->eRMS[ 13] = 0.00047751 ;
  ed->eMean[ 14] =  0.0297401  ; ed->eRMS[ 14] = 0.000402345;
  ed->eMean[ 15] =  0.030938   ; ed->eRMS[ 15] = 0.000438391;
  ed->eMean[ 16] =  0.0318146  ; ed->eRMS[ 16] = 0.000390202;
  ed->eMean[ 17] =  0.0322593  ; ed->eRMS[ 17] = 0.000394403;
  ed->eMean[ 18] =  0.032524   ; ed->eRMS[ 18] = 0.000406564;
  ed->eMean[ 19] =  0.0323994  ; ed->eRMS[ 19] = 0.000415221;
  ed->eMean[ 20] =  0.0321643  ; ed->eRMS[ 20] = 0.000389408;
  ed->eMean[ 21] =  0.0317792  ; ed->eRMS[ 21] = 0.000433731;
  ed->eMean[ 22] =  0.0312976  ; ed->eRMS[ 22] = 0.000417777;
  ed->eMean[ 23] =  0.0305421  ; ed->eRMS[ 23] = 0.000379239;
  ed->eMean[ 24] =  0.0297639  ; ed->eRMS[ 24] = 0.000428802;
  ed->eMean[ 25] =  0.0290686  ; ed->eRMS[ 25] = 0.000370367;
  ed->eMean[ 26] =  0.0282759  ; ed->eRMS[ 26] = 0.000395242;
  ed->eMean[ 27] =  0.0275665  ; ed->eRMS[ 27] = 0.000374633;
  ed->eMean[ 28] =  0.0268136  ; ed->eRMS[ 28] = 0.000339358;
  ed->eMean[ 29] =  0.0261156  ; ed->eRMS[ 29] = 0.000341921;
  ed->eMean[ 30] =  0.0253949  ; ed->eRMS[ 30] = 0.000362442;
  ed->eMean[ 31] =  0.0247598  ; ed->eRMS[ 31] = 0.000397596;
  ed->eMean[ 32] =  0.0240787  ; ed->eRMS[ 32] = 0.000386212;
  ed->eMean[ 33] =  0.0233423  ; ed->eRMS[ 33] = 0.000363384;
  ed->eMean[ 34] =  0.0227467  ; ed->eRMS[ 34] = 0.000351947;
  ed->eMean[ 35] =  0.0219522  ; ed->eRMS[ 35] = 0.000308266;
  ed->eMean[ 36] =  0.0209653  ; ed->eRMS[ 36] = 0.000439652;
  ed->eMean[ 37] =  0.0197986  ; ed->eRMS[ 37] = 0.000486246;
  ed->eMean[ 38] =  0.0183637  ; ed->eRMS[ 38] = 0.000450028;
  ed->eMean[ 39] =  0.0169368  ; ed->eRMS[ 39] = 0.00045008 ;
  ed->eMean[ 40] =  0.0155225  ; ed->eRMS[ 40] = 0.000502942;
  ed->eMean[ 41] =  0.0140819  ; ed->eRMS[ 41] = 0.000539693;
  ed->eMean[ 42] =  0.0126     ; ed->eRMS[ 42] = 0.000454148;
  ed->eMean[ 43] =  0.0111242  ; ed->eRMS[ 43] = 0.000514273;
  ed->eMean[ 44] =  0.00957784 ; ed->eRMS[ 44] = 0.000528254;
  ed->eMean[ 45] =  0.00841301 ; ed->eRMS[ 45] = 0.00049392 ;
  ed->eMean[ 46] =  0.00723504 ; ed->eRMS[ 46] = 0.000500134;
  ed->eMean[ 47] =  0.0060622  ; ed->eRMS[ 47] = 0.000331481;
  ed->eMean[ 48] =  0.00508754 ; ed->eRMS[ 48] = 0.000361306;
  ed->eMean[ 49] =  0.004231   ; ed->eRMS[ 49] = 0.000299659;
  ed->eMean[ 50] =  0.00350328 ; ed->eRMS[ 50] = 0.000299861;
  ed->eMean[ 51] =  0.00288125 ; ed->eRMS[ 51] = 0.00025348 ;
  ed->eMean[ 52] =  0.00241467 ; ed->eRMS[ 52] = 0.000241215;
  ed->eMean[ 53] =  0.00197769 ; ed->eRMS[ 53] = 0.000232315;
  ed->eMean[ 54] =  0.00162581 ; ed->eRMS[ 54] = 0.000243514;
  ed->eMean[ 55] =  0.00136063 ; ed->eRMS[ 55] = 0.000220774;
  ed->eMean[ 56] =  0.00110661 ; ed->eRMS[ 56] = 0.00019364 ;
  ed->eMean[ 57] =  0.000950109; ed->eRMS[ 57] = 0.000199918;
  ed->eMean[ 58] =  0.000847732; ed->eRMS[ 58] = 0.000190454;
  ed->eMean[ 59] =  0.000702041; ed->eRMS[ 59] = 0.000187732;
  ed->eMean[ 60] =  0.000618623; ed->eRMS[ 60] = 0.000181209;
  ed->eMean[ 61] =  0.000558599; ed->eRMS[ 61] = 0.000197058;
  ed->eMean[ 62] =  0.000520909; ed->eRMS[ 62] = 0.000199729;
  ed->eMean[ 63] =  0.000517644; ed->eRMS[ 63] = 0.000226821;
  ed->eMean[ 64] =  0.000423366; ed->eRMS[ 64] = 0.000181341;
  ed->eMean[ 65] =  0.000369895; ed->eRMS[ 65] = 0.000208552;
  ed->eMean[ 66] =  0.000367252; ed->eRMS[ 66] = 0.000196718;
  ed->eMean[ 67] =  0.000358556; ed->eRMS[ 67] = 0.00021259 ;
  ed->eMean[ 68] =  0.000326886; ed->eRMS[ 68] = 0.000190518;
  ed->eMean[ 69] =  0.000292097; ed->eRMS[ 69] = 0.000180116;
  ed->eMean[ 70] =  0.000298525; ed->eRMS[ 70] = 0.000162377;
  ed->eMean[ 71] =  0.000273385; ed->eRMS[ 71] = 0.000172078;
  ed->eMean[ 72] =  0.000219399; ed->eRMS[ 72] = 0.000161089;
  ed->eMean[ 73] =  0.000210825; ed->eRMS[ 73] = 0.000164644;
  ed->eMean[ 74] =  0.000173816; ed->eRMS[ 74] = 0.000156155;
  ed->eMean[ 75] =  0.000175219; ed->eRMS[ 75] = 0.000162768;
  ed->eMean[ 76] =  0.000163239; ed->eRMS[ 76] = 0.000173306;
  ed->eMean[ 77] =  0.000187567; ed->eRMS[ 77] = 0.000183058;
  ed->eMean[ 78] =  0.000112925; ed->eRMS[ 78] = 0.000197073;
  ed->eMean[ 79] =  0.000212973; ed->eRMS[ 79] = 0.000199585;
  ed->eMean[ 80] =  0.000139594; ed->eRMS[ 80] = 0.000166878;
  ed->eMean[ 81] =  0.000167285; ed->eRMS[ 81] = 0.000184349;
  ed->eMean[ 82] =  0.000179766; ed->eRMS[ 82] = 0.000167843;
  ed->eMean[ 83] =  0.000141419; ed->eRMS[ 83] = 0.000174631;
  ed->eMean[ 84] =  0.000175728; ed->eRMS[ 84] = 0.000147563;
  ed->eMean[ 85] =  0.000162536; ed->eRMS[ 85] = 0.000167244;
  ed->eMean[ 86] =  0.000134914; ed->eRMS[ 86] = 0.000154353;
  ed->eMean[ 87] =  0.000137469; ed->eRMS[ 87] = 0.000184225;
  ed->eMean[ 88] =  0.000123097; ed->eRMS[ 88] = 0.000175981;
  ed->eMean[ 89] =  0.000128892; ed->eRMS[ 89] = 0.000172444;
  ed->eMean[ 90] =  0.000123729; ed->eRMS[ 90] = 0.000171074;
  ed->eMean[ 91] =  0.000108401; ed->eRMS[ 91] = 0.000220211;
  ed->eMean[ 92] =  7.01413e-05; ed->eRMS[ 92] = 0.000205878;
  ed->eMean[ 93] =  9.66169e-05; ed->eRMS[ 93] = 0.000221296;
  ed->eMean[ 94] =  8.07938e-05; ed->eRMS[ 94] = 0.00020561 ;
  ed->eMean[ 95] =  9.59974e-05; ed->eRMS[ 95] = 0.000210794;
  ed->eMean[ 96] =  0.000114446; ed->eRMS[ 96] = 0.000190085;
  ed->eMean[ 97] =  6.29018e-05; ed->eRMS[ 97] = 0.000214778;
  ed->eMean[ 98] =  0.000136174; ed->eRMS[ 98] = 0.00019899 ;
  ed->eMean[ 99] =  8.47347e-05; ed->eRMS[ 99] = 0.000165493;
  ed->eMean[100] =  9.65548e-05; ed->eRMS[100] = 0.000162461;
  ed->eMean[101] =  0.000108493; ed->eRMS[101] = 0.000158595;
  ed->eMean[102] =  0.000134108; ed->eRMS[102] = 0.000171021;
  ed->eMean[103] =  9.13547e-05; ed->eRMS[103] = 0.000185802;
  ed->eMean[104] =  0.000182827; ed->eRMS[104] = 0.000179139;
  ed->eMean[105] =  0.000125751; ed->eRMS[105] = 0.000188626;
  ed->eMean[106] =  0.000109692; ed->eRMS[106] = 0.00017541 ;
  ed->eMean[107] =  0.000136805; ed->eRMS[107] = 0.000173494;
  ed->eMean[108] =  0.000134697; ed->eRMS[108] = 0.00019583 ;
  ed->eMean[109] =  0.000103055; ed->eRMS[109] = 0.000198063;
  ed->eMean[110] =  7.88266e-05; ed->eRMS[110] = 0.000186962;
  ed->eMean[111] =  0.000111834; ed->eRMS[111] = 0.000199749;
  ed->eMean[112] =  7.27311e-05; ed->eRMS[112] = 0.000195761;
  ed->eMean[113] =  9.14903e-05; ed->eRMS[113] = 0.000184388;
  ed->eMean[114] =  5.74501e-05; ed->eRMS[114] = 0.000181336;
  ed->eMean[115] =  0.000107116; ed->eRMS[115] = 0.000195444;
  ed->eMean[116] =  0.000103824; ed->eRMS[116] = 0.000199098;
  ed->eMean[117] =  0.000109764; ed->eRMS[117] = 0.000187299;
  ed->eMean[118] =  0.000104725; ed->eRMS[118] = 0.000193595;
  ed->eMean[119] =  8.40021e-05; ed->eRMS[119] = 0.000194996;
}


EventSim::~EventSim() {
}


// get an event
const Event* EventSim::get() {
  if ( nMax-- ) return generate();
  return nullptr;
}


// generate an event
const Event* EventSim::generate() {

  // set event id
  evId += ceil( randE( 10.0 ) );

  // create a new event
  Event* ev = new Event( evId );

  // choose channel
  float frac = randF();
  ElementData* element;
  vector<ElementData*>::const_iterator iter = eData.begin();
  while ( frac > 0 ) {
    element = *iter++;
    frac -= element->evFrac;
  }

  // simulate energy loss fractions
  int n = Event::minSize;
  float* e = new float[n];
//  float  s = 0;
  while ( n-- ) //s +=
                ( e[n] = randG( element->eMean[n], element->eRMS[n] ) );

  // simulate total energy
  float energy = randG( element->eTotMean , element->eTotRMS );// / s;

  // rescale point energy losses and add to event
  int m = Event::minSize;
  while ( ++n < m ) ev->add( lround( ( e[n] * energy ) +
                                     randG( pedestalMean, pedestalRMS ) ) );
  delete[] e;

  // add background tail
  m = lround( randF( m, Event::maxSize ) );
  while ( n++ < m ) ev->add( lround( randG( pedestalMean, pedestalRMS ) ) );

  return ev;

}


// generate an event
EventSim::ElementData* EventSim::createElement( float evFrac,
                                                float eTotMean,
                                                float eTotRMS ) {
  ElementData* ed = new ElementData;
  ed->evFrac   = evFrac;
  ed->eTotMean = eTotMean;
  ed->eTotRMS  = eTotRMS;
  ed->eMean.resize( Event::minSize );
  ed->eRMS .resize( Event::minSize );
  return ed;
}

