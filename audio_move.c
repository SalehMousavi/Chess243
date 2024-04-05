#include <stdlib.h>
#include <stdio.h>

const int left_channel[] = {
-1170, 1159, -1148, 1137, -1126, 1115, -1104, 1093, -1082, 1071, -1060, 1049, -1038, 1027, -1016, 1005, -994, 983, -972, 961, -950, 939, -928, 916, -905, 894, -883, 872, -861, 849, -838, 827, -816, 804, -793, 782, -771, 759, -748, 737, -725, 714, -703, 691, -680, 669, -657, 646, -634, 623, -611, 600, -588, 577, -565, 554, -542, 531, -519, 508, -496, 484, -473, 461, -449, 438, -426, 414, -403, 391, -379, 368, -356, 344, -333, 321, -309, 297, -286, 274, -262, 251, -239, 227, -216, 204, -192, 181, -169, 157, -146, 134, -123, 111, -100, 88, -77, 66, -54, 43, -32, 21, -10, 0, 11, -22, 33, -43, 54, -64, 74, -84, 94, -104, 114, -123, 132, -141, 150, -159, 167, -175, 183, -190, 197, -203, 209, -215, 220, -225, 229, -232, 234, -236, 237, -237, 236, -234, 231, -226, 220, -213, 203, -191, 178, -161, 142, -120, 94, -64, 29, 10, -56, 110, -173, 246, -333, 435, -559, 713, -912, 1204, -1801, 5247, 115870, 149333, 32590, -6726, 3044, -1950, 2592, -11102, -50583, 39508, 25665, 223899, 231851, 962, -137214, -324667, -47828, -135, 5558, -7256, 8459, -10809, 24627, 176938, -12866, -395911, -70910, 14148, -7723, 26878, 165211, -126535, -426802, -36777, 68852, -12921, 12, 31850, 53768, -26147, 28598, -155584, -460647, -608968, -570606, 53891, 45772, 232257, 63805, -128516, -89899, -179835, 80932, -94549, -412760, -436095, 182763, 275106, 412813, 178939, 30185, 80881, 18610, -242327, -511851, -144466, -20054, 271523, 192654, -13626, -440270, -479734, -9582, -475553, -490466, -260712, 143789, 52937, -30539, 30857, -43566, 236012, 219183, -42625, -389424, -362461, 362644, 517203, 410197, 145512, -111180, -372543, 355052, 1126979, 322213, -19568, 28801, 399536, 594959, -8542, 216457, 109152, -1726, -58664, -387844, -28871, 827332, 1560894, 1623991, 1650516, 1200260, 142278, -1117798, -2269873, -1761511, 54031, 1633446, 3146532, 7156066, 7505830, 3809964, 381236, -2340879, -4621452, -5809832, -5207850, 1404474, -13258119, -22897810, -21080420, -14934605, -16889437, -16134587, 568353, -19116400, -103108043, -302216422, -644291895, -1003535224, -937698842, 29511481, 1471814817, 2147483647, 1650140929, 654148858, -91189021, -398693996, -526763482, -527220947, -432463113, -276536914, -51634192, 24827584, -220811095, -531105711, -416674140, -19850638, 298013126, 398590195, 156772578, -168184282, -145883173, 4733398, -75060931, -206998504, -135919446, 6332720, -5094508, -11965280, 49584030, -51759597, -309305114, -492400669, -396235355, -104810119, 209822681, 495505430, 665036958, 639364976, 365411270, -129903913, -376297550, -135125127, 171566976, 219504713, 107275853, -53522131, -196617655, -211898181, -134041332, -30189129, 73967164, 110834790, 140507466, 244791205, 321129854, 229135108, -47121805, -282760131, -324856326, -229300834, -96252194, -47748613, -116072691, -191515294, -189745646, -108551872, -1927692, 77415231, 83064137, 64302420, 126375910, 239021673, 261220400, 144210901, -83029322, -303286961, -341805226, -174972688, 2159917, 92170314, 120972391, 67559410, -22023655, -57867929, -57893275, -22091604, 63559721, 151346153, 196036117, 188126886, 131878405, 37272197, -29649978, -16374975, 33468668, 78926859, 89566122, 38095601, -76740882, -176759009, -188529735, -103074378, 54574092, 193070929, 217291417, 155120268, 71620074, -14539960, -91522958, -147658073, -170859643, -157916819, -119500249, -78255287, -42224017, -24014407, -22338771, -6456695, 36861415, 81320723, 114706047, 117210044, 91704052, 44806373, -12980574, -55657099, -68665757, -54031128, -36272265, -35984557, -47306921, -60912108, -71572497, -69485900, -43739270, 7915415, 53685368, 79017030, 91187692, 95032375, 90956393, 69723873, 31413089, -4728671, -23533240, -14222132, 5200176, 15757392, -7180778, -51086908, -84033543, -85709401, -53294484, -10976803, 20228484, 42550361, 53929566, 40651844, 6086740, -27998496, -41358248, -31141558, -9824085, -2408923, -20231935, -44401111, -47810554, -24820703, 9217282, 28534059, 28902561, 18951994, 11188841, 13611843, 22522747, 30470710, 27059963, 9163544, -12935488, -25669398, -25289862, -15530445, -1078712, 7359906, 2973755, -8414468, -15577845, -9305042, 6592239, 17182662, 16062018, 10990016, 10570743, 7447367, -2939782, -16514835, -25123619, -24074257, -17348276, -9678825, -640515, 5533562, 6222577, 31036, -7201988, -9587564, -4917997, 7800965, 22915180, 30970796, 29457381, 23021684, 16246591, 7364061, -3131292, -11377620, -12675520, -4590420, 6790441, 8533015, -671455, -14015488, -20926869, -15061543, -5338227, -1446500, -915957, -49794, 1143461, 1002302, -2044446, -6917249, -8390215, -4046506, 623847, -354113, -4935501, -8730464, -7538576, -2944899, 1008612, 3329650, 8988621, 17845418, 23165841, 18993897, 7356145, -3393290, -6675897, -3340448, 1721907, 3308463, 2373412, 1926048, 1560987, 104118, -1197202, -280983, 5540258, 12098535, 13529851, 9409483, 5021562, 3224013, 3925479, 3789144, -582558, -6368221, -10371861, -12125055, -12037060, -8757672, -3718236, -2641033, -5929088, -9966425, -10568478, -6329212, 1904472, 7799864, 5791775, -2200180, -9875817, -11559041, -6027656, 3656558, 12207293, 13533091, 6774418, -868927, -3039143, 804421, 6520241, 8925856, 8441604, 5836831, 1651285, -702292, 1655001, 5408462, 5899186, 3784759, 867981, -990750, -113351, 1444000, 70169, -3105137, -5038090, -5625096, -4690828, -2334693, -258363, -2031272, -7274284, -13212840, -17070309, -15488563, -6355022, 4606392, 11223717, 13079460, 11282422, 6116191, -1050148, -6726780, -8166472, -4565421, 990367, 3659481, 4544118, 5342548, 6140797, 6076465, 4480191, 1918875, -1382624, -3947242, -3431712, -333514, 2378207, 1993299, -1171757, -5557061, -7121828, -3682659, 1868488, 4771396, 2562425, -4827665, -11944012, -12983781, -8786798, -3401221, 947250, 3972406, 6302244, 7356624, 6152355, 3593356, 595760, -2141553, -1681293, 1455447, 3703902, 3276549, 2030339, 1277524, 1090325, 841259, -1045674, -2213782, -354715, 1923471, 1619275, -73870, -1218665, -2524861, -4076945, -5238945, -4704498, -3055333, -513268, 1585409, 1355498, -1687462, -4769470, -5369854, -3271544, 535886, 2966741, 2189577, 799234, 19158, -1511340, -3338519, -4097343, -2476442, 826161, 2876398, 5263619, 8770387, 8641246, 3093118, -3579298, -7774874, -8902476, -6300309, -521867, 6249688, 10885162, 10182294, 4728257, -2111703, -6256481, -5983750, -2699686, 958223, 3342952, 3401897, 1667890, 363614, -267935, -2017917, -2981116, -485708, 3911271, 4927365, 1782538, -2375550, -5110041, -6816569, -7563592, -6105414, -2472287, 1235670, 4119052, 3959874, -1102465, -7195129, -10060656, -7020197, 1770683, 9806610, 11240983, 7203429, 2438404, -425544, -1969869, -2574881, -1743246, -405971, -75496, -1304621, -3625224, -6375470, -5195928, 1680910, 8696487, 11378800, 9954585, 7266541, 6384930, 6296808, 4680237, 421142, -4893846, -7085928, -4793036, -1203278, 133573, -1763631, -4967469, -7809497, -8654831, -7854658, -6550741, -3569010, 742933, 4418113, 6575382, 6239465, 4662218, 2348403, -117725, -847157, 573688, 973311, -2124361, -6078829, -7050132, -5036410, -915585, 2781407, 5333469, 7729148, 8714519, 7409208, 5239769, 3542584, 2139857, 1693791, 2245929, 2031652, -473249, -4806699, -7359410, -7198715, -6195547, -5819318, -4239114, -480881, 3773182, 5238493, 2269600, -1099777, -1537033, -496000, 865219, 1892237, 1030943, -1426583, -2632594, -2212390, -1609280, -1887579, -1948834, -178817, 4349486, 8297596, 7097812, 1639944, -3707396, -5907100, -3712761, 1243905, 6462066, 8083675, 4690282, -215374, -3279691, -3872952, -4086621, -4920528, -3948016, -1556867, -147869, 736247, 2226170, 2413697, 643608, -495443, 117416, 1238918, 1087687, -1988268, -5534742, -4983506, -1615120, 311831, 272982, 1131614, 3283644, 4907679, 4434447, 1686081, -1031290, -1012961, 78583, 270322, -430971, -1378295, -2075598, -2624430, -2726673, -3145690, -3158772, -379403, 3894834, 4722349, 937310, -3946584, -6046701, -2753634, 4612536, 9554934, 7962073, 2447865, -2804137, -5383718, -5249044, -3858681, -1894111, 429889, 3565539, 5853648, 4330293, -1232427, -5344751, -4504499, -1179146, -83944, -2754999, -6199428, -6308663, -2671778, 2608683, 6865079, 7322769, 3896756, -281740, -1954202, -1341261, -488648, -572612, -1361221, -561343, 1178170, 1300508, 306744, 527951, 1151951, -429901, -3524176, -4206800, -1351016, 2078763, 3970539, 4242239, 3508219, 2332272, 1213138, -268677, -1788424, -2405782, -2169562, -1230413, -1019203, -2384204, -4074587, -3910996, -1220590, 1950025, 3604789, 4528375, 4498797, 2317565, -1330672, -4064434, -4639730, -3134351, -630863, 462788, -5206, -1016602, -2321135, -2608627, -1216162, 690341, 2274710, 3832785, 5362231, 5409627, 4250646, 3954342, 4109062, 2395869, -2485957, -8404559, -10410611, -7466894, -2311571, 1859083, 3009442, 2510581, 1266822, 92070, -210257, 436913, 1442926, 2762540, 2999314, 468198, -2578592, -2932547, -1503726, 686454, 2407455, 1924589, -50353, -2249997, -4496010, -5513720, -3722690, 358505, 3197680, 3553295, 2979880, 2721408, 2770757, 2056031, 22851, -2033272, -3461071, -3952748, -3475291, -1809393, 1522602, 4244272, 3359635, 94646, -2225173, -1383512, 2370509, 5364712, 4271000, 1384032, -569161, -2801707, -6481324, -9628432, -8957575, -3968505, 2396067, 6855055, 7187424, 3840700, -797561, -3707967, -3443538, -975426, 1528038, 2705994, 2758399, 2209237, 774225, -1201594, -2719536, -2737142, -2063496, -1729881, -1318637, -365001, 816531, 1360220, 1206235, 1983343, 3722902, 4947329, 5333539, 4413759, 2218997, -606884, -3390286, -4781676, -4942864, -4531568, -3159192, -246506, 2568585, 1415548, -3136658, -5910970, -4210866, 27039, 3316923, 4915127, 5025775, 3223719, -62445, -3211280, -4651130, -4373120, -3108184, -1559366, -43510, 1417314, 2235865, 2587657, 2680504, 1728971, -376938, -2402633, -2308398, 848404, 4283221, 4491099, 1992546, -328187, -1004438, -926050, -1542937, -2940810, -3806818, -2085673, 1606691, 3964619, 2512558, -752683, -1602745, 1225510, 4690468, 5759796, 3601320, 239401, -2387753, -4111403, -5649245, -6009107, -3876310, -1363477, -844923, -1148407, -629062, 248822, 838233, 1417238, 1298883, 850904, 923567, 640179, -1400877, -3751125, -4300677, -3310246, -1126459, 2079753, 4572418, 4796725, 4070699, 3843407, 2877371, 973412, -282874, -818598, -1338718, -1234616, -712061, -446092, 291887, 1525387, 1544398, 98446, -1323843, -2444911, -4086210, -5166551, -4834333, -3124710, 311250, 4614067, 7147154, 6392762, 3610275, 671361, -1846937, -3272914, -3977538, -4681416, -4126546, -1885822, 1081109, 3269758, 3814493, 3133875, 1348799, -941975, -1480059, -422430, 69923, -949667, -2624932, -3590329, -2175894, 1527655, 3903028, 3150022, 816871, -1079239, -1322908, -64258, 640352, 589934, 885554, 1825168, 2631477, 1743645, -1227624, -4073631, -4551859, -2567262, 447926, 2456968, 2427092, 1661237, 1012751, 187769, -107260, 418850, 969970, 552011, -1000983, -2725824, -3721447, -3762168, -2405040, 34078, 2181694, 2527255, 1222454, -791051, -2013135, -1382225, -200205, -12701, 256074, 1784180, 2852397, 2583871, 1879593, 1545085, 973860, -282058, -1801471, -3050811, -3457296, -2627901, -1114882, 135945, 1482096, 2925201, 2717301, 863551, -894832, -1584553, -1372637, -846763, -667150, -1080939, -1936051, -2200057, -1597892, -405553, 1095741, 2718145, 3661770, 3247331, 1872615, 223601, -1152706, -1724902, -1794469, -1778675, -1700997, -780061, 761236, 1214306, -52356, -1609875, -1810306, -351094, 1867023, 3872418, 4279691, 3004245, 1106724, -1453826, -3788429, -4058209, -2597056, -903695, 376590, 1064206, 953184, -371101, -1886196, -2121562, -1504314, -761520, 83196, 1210951, 1814371, 1104449, -1019134, -2705377, -1663359, 1661063, 4123311, 4097352, 2073774, -412362, -2355321, -2640822, -1493084, -264936, 405992, 1337234, 2185183, 2113186, 834376, 24455, -112329, -1127999, -2627080, -3437027, -3033692, -1646920, -97488, 1225732, 2388160, 2656364, 1770889, 847232, 763219, 965243, 144035, -1764110, -3262454, -3588842, -3471962, -2809508, -904167, 1883240, 3698388, 3511554, 1783425, 231654, 104173, 1135434, 1813679, 911278, -846329, -1784810, -806129, 620418, 183646, -1554388, -2659551, -2365303, -1332251, -227382, 443109, 793621, 901473, 568066, 87580, -6910, 530697, 1138575, 1201011, 854716, 327318, -725856, -1724905, -1688824, -883794, 335505, 1564391, 2244162, 1497381, 133228, -510597, -660660, -1010633, -1134437, -195122, 1259300, 1328589, -549067, -2708933, -3057709, -1486094, 430696, 1063830, 633904, 190281, 331973, 560749, 520747, 179513, -38224, 128271, 509912, 455120, -385561, -1514199, -2007818, -1644376, -1072897, -655051, -132093, 898335, 2351243, 3138195, 2229425, 76908, -1624405, -1856453, -1296379, -875384, -816867, -828348, -750584, -306100, 430024, 892294, 955900, 1035604, 1238012, 820255, -325026, -897047, -288681, 524281, 523134, -505159, -1491882, -1580394, -1365351, -797146, 165018, 1105206, 1291652, 765289, 345122, 95974, -2360, -5612, 118403, 790404, 824339, -110286, -1325056, -2299037, -2411170, -1545196, -130124, 1007746, 1386519, 1365950, 1375483, 1286388, 252505, -1613041, -2369075, -953551, 1448988, 2510279, 1882029, 632798, -932157, -2536582, -3157165, -2333597, -595338, 1057686, 2189292, 2703418, 2331492, 773450, -1185758, -1835133, -557104, 1470300, 2605327, 1478187, -1251851, -3700866, -4371261, -3295911, -1360916, 53481, 811598, 1873847, 2966335, 2907166, 1780186, 455091, -559832, -972984, -906280, -369662, 126549, 58360, -452266, -1030293, -1320626, -1802122, -2079988, -1504069, 413663, 2791741, 3859950, 2978713, 1122007, -615085, -1261524, -1240089, -1226188, -1223421, -666857, 54616, 65583, -706600, -1588939, -1752231, -927237, 301282, 783083, 529846, 217348, 126522, 20727, -7159, 4676, -3720, 3244, -2975, 2808, -2699, 2624, -2570, 2530, -2498, 2473, -2452, 2434, -2418, 2404, -2390, 2377, -2365, 2353, -2341, 2329, -2317, 2305, -2294, 2282, -2270, 2258, -2247, 2235, -2223, 2211, -2199, 2187, -2175, 2163, -2151, 2139, -2127, 2115, -2103, 2091, -2079, 2067, -2055, 2043, -2031, 2019, -2007, 1995, -1983, 1971, -1959, 1947, -1935, 1923, -1912, 1900, -1888, 1876, -1865, 1853, -1841, 1829, -1818, 1806, -1795, 1783, -1772, 1760, -1749, 1737, -1726, 1714, -1703, 1691, -1680, 1669, -1657, 1646, -1635, 1624, -1612, 1601, -1590, 1579, -1568, 1556, -1545, 1534, -1523, 1512, -1501, 1490, -1478, 1467, -1456, 1445, -1434, 1423, -1412, 1401, -1390, 1379, -1368, 1357, -1346, 1335, -1324, 1313, -1302, 1291, -1280, 1269, -1258, 1247, -1236, 1225, -1214, 1203, -1192, 1181, };

const int right_channel[] = {
78, -88, 98, -108, 118, -128, 138, -148, 158, -168, 178, -188, 198, -209, 219, -229, 239, -250, 260, -270, 281, -291, 302, -312, 323, -333, 344, -355, 365, -376, 387, -397, 408, -419, 430, -441, 451, -462, 473, -484, 495, -506, 517, -529, 540, -551, 562, -573, 585, -596, 607, -619, 630, -641, 653, -664, 676, -687, 699, -711, 722, -734, 746, -757, 769, -781, 793, -804, 816, -828, 840, -852, 864, -876, 888, -900, 912, -924, 936, -948, 960, -972, 984, -996, 1008, -1020, 1033, -1045, 1057, -1069, 1081, -1093, 1105, -1117, 1129, -1141, 1154, -1166, 1177, -1189, 1201, -1213, 1225, -1237, 1248, -1260, 1271, -1283, 1294, -1306, 1317, -1328, 1339, -1349, 1360, -1370, 1381, -1391, 1400, -1410, 1419, -1428, 1437, -1446, 1454, -1461, 1469, -1476, 1482, -1488, 1493, -1498, 1502, -1505, 1507, -1509, 1509, -1509, 1507, -1504, 1499, -1493, 1485, -1475, 1463, -1448, 1431, -1410, 1386, -1358, 1325, -1287, 1242, -1190, 1129, -1058, 974, -873, 751, -600, 402, -113, -481, 3925, 117194, 148006, 33919, -8058, 4378, -3286, 3931, -12443, -49239, 38161, 27014, 222547, 233205, -394, -135854, -326029, -46463, -1504, 6929, -8630, 9837, -12190, 26011, 175550, -11475, -397304, -69513, 12747, -6319, 25470, 166623, -127950, -425382, -38200, 70279, -14352, 1447, 30411, 55211, -27595, 30051, -157040, -459185, -610433, -569135, 52415, 47252, 230771, 65295, -130011, -88398, -181342, 82444, -96067, -411236, -437625, 184299, 273563, 414362, 177383, 31747, 79312, 20186, -243910, -510260, -146065, -18447, 269909, 194276, -15257, -438630, -481383, -7923, -477221, -488787, -262400, 145488, 51227, -28817, 29123, -41819, 234252, 220956, -44412, -387623, -364278, 364476, 515353, 412064, 143626, -109274, -374469, 357000, 1125006, 324210, -21593, 30855, 397450, 597078, -10699, 218654, 106911, 564, -61011, -385433, -31353, 829897, 1558228, 1626773, 1647585, 1203373, 138919, -1114095, -2274096, -1756364, 46708, 1655167, 3152802, 7156193, 7501858, 3788424, 383638, -2341526, -4621613, -5809066, -5209332, 1408030, -13234249, -22911268, -21102880, -14950782, -16873663, -16106405, 573763, -19117479, -103106791, -302172377, -644289806, -1003539856, -937723755, 29532977, 1471822798, 2147483647, 1650131402, 654128861, -91183071, -398701610, -526802855, -527237170, -432506491, -276544711, -51609744, 24827399, -220763530, -531057656, -416584360, -19886234, 298008371, 398707812, 156858683, -168225108, -145969080, 4707720, -75125822, -207006010, -136042860, 6132705, -5212542, -11974538, 49656883, -51599384, -309229582, -492311460, -396071804, -104632773, 210021352, 495908988, 666135478, 641744278, 369254918, -125899107, -375918565, -140904877, 162028221, 210736054, 101279645, -57688638, -198848301, -209213051, -125323016, -19233027, 82077698, 113817596, 139956807, 243822515, 320920815, 228862569, -48713357, -285119680, -326864953, -230389050, -97573421, -51399887, -121387129, -195718261, -189801868, -102689497, 7026216, 85037751, 87265903, 64928743, 124975673, 237355014, 260396890, 143948548, -83814970, -304103519, -342642028, -177692019, -4421004, 82612476, 113166396, 65919068, -16681997, -48803090, -50345560, -18158729, 64121422, 147757600, 189266799, 183172979, 133427141, 45204264, -18766345, -7087790, 36108562, 72575486, 77313274, 26358834, -82291931, -176038812, -184940073, -98475662, 59309023, 195201773, 214465381, 150712761, 71589148, -8767219, -83717894, -142658029, -170241549, -160463046, -124970382, -85184083, -47396244, -25600271, -21667468, -4885451, 39874539, 86423039, 120734913, 121066250, 90742263, 40380478, -17269227, -56923096, -67674658, -55760329, -43745194, -46546585, -54309287, -58591234, -61952307, -60408934, -39455089, 8787186, 51646164, 73887475, 87177537, 96942609, 98477235, 78698179, 38696241, 12298, -21341384, -14922545, 1675346, 10035008, -12605765, -53721738, -84666525, -87103423, -56495236, -13004786, 22557852, 47328832, 57380646, 41182659, 3926802, -32158248, -47059623, -38791903, -18386801, -7938833, -20443782, -41183405, -43622861, -20183976, 13535274, 30722482, 28702118, 19495929, 13004498, 14447481, 24114160, 34567710, 31352815, 11270772, -12426610, -25479143, -24759027, -14598673, -2023927, 3584977, -1465894, -10909207, -13962744, -3553811, 14221509, 23497468, 18724469, 10018858, 7784411, 2625509, -9581154, -21370281, -26073258, -23210395, -17002671, -11520640, -6044199, -110817, 5071931, 4656111, 347737, -4830198, -6306905, 2353858, 18086511, 28954373, 30593174, 26537751, 21205268, 11950037, -2894904, -16746316, -18616825, -7804715, 5024096, 7366711, -1504034, -14672302, -22050097, -16845376, -6287236, 211993, 3965794, 7124195, 8278983, 5049178, -598305, -4294162, -4696547, -2111384, -695744, -5359688, -9108941, -7411252, -3794833, -1984354, 66043, 3872536, 9907865, 16048284, 18895607, 14746067, 6123102, -472595, -1777799, -617848, -618915, -2062798, -2040340, 976616, 4077741, 989095, -6479219, -9093441, -2065277, 8571569, 15986746, 17312730, 12983378, 6433635, 3956038, 3409800, -438493, -5827271, -9771168, -11559790, -11449414, -8251761, -3719466, -2258617, -4060026, -7200093, -10182829, -10204829, -4844942, 1638799, 4775611, 4017944, 1144432, -843445, 1355315, 6086237, 7459871, 3314709, -2382212, -3998392, -1141517, 3441569, 6142692, 5414337, 4152633, 3342729, 2136820, 1161094, 1289453, 1561351, 1844216, 3287808, 4223122, 3357221, 2470696, 1911538, 305265, -1465349, -2042628, -3221871, -5328408, -5612052, -3825073, -3288717, -5775553, -10378934, -13721648, -12688813, -6381859, 705775, 6475314, 11731427, 12606112, 6964949, -593585, -5155113, -5133846, -2533622, 722729, 2551172, 3152457, 2096197, -385447, -1866560, 47947, 4284644, 6448730, 5340661, 2871614, -253664, -3702224, -5711203, -5603635, -4970194, -3565361, -1153746, 1268403, 1496340, 646518, -1411203, -4447969, -5993231, -5638908, -3945552, -644642, 2372081, 4914601, 6133212, 4605382, 2836379, 1201978, -991043, -888361, 1776355, 3283305, 1149988, -1236504, -1824150, -524990, 2165109, 2325787, 63744, -746834, 1124914, 3012637, 2198746, -667919, -3173618, -2853063, -982569, -1553672, -5080544, -7833194, -7594987, -5157137, -3446745, -2689248, -2173682, -1249088, 2396426, 7517867, 7904179, 4436207, 2757765, 4009524, 4452779, 265527, -6959071, -10973911, -8253271, -1016445, 4685260, 6419010, 6359681, 5077176, 622131, -5179876, -6884340, -5230201, -2479234, 2448947, 6444341, 5912753, 2540301, 266745, 440606, 1370808, 1266225, 223869, -955121, -1156455, -220006, 778484, 628741, 257557, 522647, 938332, 902187, -499255, -4669604, -8200430, -7181680, -3860854, -2643238, -3225005, -2333840, 1508114, 5810417, 7576787, 6376800, 3608330, 452664, -1677111, -1843750, -310341, 989745, -828326, -5265862, -7179735, -4842801, -1061757, 1444159, 2268853, 1791532, 996749, 794864, 1698050, 3728525, 5514526, 5905188, 4425716, 1203964, -1234854, -2030352, -1892449, -943350, 281853, 691564, 466415, 7357, 171816, 552234, -255425, -2065489, -3930028, -4561592, -3531835, -3052545, -3609997, -3532773, -1097130, 2706370, 5505466, 5987598, 3791088, 306041, -1841014, -1652462, -163259, 528611, 760805, 1261958, 1781081, 961920, -937387, -2026821, -1832972, -1088923, 1398486, 5390072, 6567349, 3549021, -959768, -2835719, -949776, 923071, 736013, -1479464, -2987355, -3400984, -3968642, -4181821, -2941729, -1145649, -379722, 1380565, 4912310, 5996089, 2651297, -1679544, -4303418, -3623091, 217552, 3036667, 2567551, 826616, -695810, -2791885, -3819947, -3225720, -2635908, -1392778, 722559, 3030544, 5479224, 8029502, 10449634, 9886851, 2549256, -8671794, -14693253, -8964407, 2450117, 8634148, 6549757, 397619, -4400836, -5970449, -4085613, -1319801, 48556, 2340374, 5281480, 5149725, 676259, -4093414, -6014902, -4281689, -93017, 1767456, -111785, -1355279, -1015764, -2084425, -3759115, -4491612, -2968602, 529942, 4790640, 8785590, 9873018, 7016874, 2100637, -2454608, -5029142, -5173272, -2756412, 595118, 2776346, 1599995, -3298546, -7507622, -5605975, 755682, 6900705, 10058989, 8504055, 2604323, -4202073, -8491139, -9009878, -6813506, -3027146, 1257797, 4320622, 4489362, 2150137, -1149176, -4403199, -4897141, -1164259, 3601347, 6118230, 5617940, 3460631, 1211913, -636604, -2461659, -3768942, -4238723, -3814638, -3004198, -2144470, -1509665, -577460, 213916, 441694, 1362527, 3988541, 6610075, 6600009, 3659695, -1052078, -5508613, -7524909, -6286447, -3127507, -392513, 401603, 421201, 693971, 374652, -900065, -1981824, -913422, 3059165, 7713554, 9034259, 5747328, 941081, -2400554, -4302572, -5097867, -4252255, -2147497, -290924, 717067, -29254, -2501019, -3545135, -1787285, 802873, 3451094, 5639867, 5904159, 3852965, 616060, -2848728, -5449994, -5696542, -3673974, -1965393, -1230725, -228871, 442955, 297729, 769905, 2344419, 3803445, 4441666, 3867020, 2112479, -47691, -2423605, -4643788, -5506999, -3563846, 87046, 2441838, 2851649, 2535449, 2127590, 583432, -2484110, -4170715, -2659548, 714884, 3527377, 3887634, 1601504, -1069592, -2401207, -2704840, -3035101, -3314585, -2918794, -1222336, 1141225, 2354856, 1351147, -497099, -327065, 2321152, 3852603, 2870136, 1251915, -80112, -1191125, -1744242, -1784759, -1706479, -1037663, 51682, 365181, -247507, -1548664, -2891504, -2173824, 1242789, 4141342, 4058577, 2267662, 1491814, 1654806, 1057075, -432563, -2136150, -3288602, -3579208, -3383647, -2472223, -14250, 3012902, 4502309, 4580292, 3996396, 1268540, -3382119, -5799872, -4075286, -1253932, -535163, -2566849, -5246635, -5315587, -791231, 5426945, 8078604, 6595184, 3602246, 952241, -1078281, -2270019, -2324133, -1047207, 1099611, 2703741, 1820591, -1137000, -3824385, -4083223, -2389077, -330790, 926894, 880507, 392344, 763733, 1627451, 2007777, 1487008, 968675, 872024, 404886, -763729, -1685775, -1905343, -1616479, -1370525, -1753044, -2709886, -2899857, -1313488, 345446, 774655, 1004299, 2093232, 3083244, 3065575, 2347997, 1204855, 149447, -455086, -958442, -1951582, -3043185, -3287195, -2601756, -1265747, 654685, 2447913, 3511477, 3595643, 1896345, -583376, -1239633, -126304, 576220, -327766, -1841794, -2870926, -3619363, -3709050, -2059005, 264232, 1374720, 1285195, 1153661, 1887435, 2887326, 3084142, 2385213, 944580, -946372, -2075585, -1773982, -477809, 1025769, 1689750, 959180, -300843, -1578949, -3167061, -4355455, -3053248, 442871, 3154404, 3808683, 2709894, 409125, -1482226, -1246589, 233099, 917006, 24800, -1076750, -1873154, -1956515, -1251919, -419903, 55545, 550920, 592858, -2177, 221974, 1251520, 1099459, 255518, 553715, 1275699, 990519, 36152, -563565, -306331, 239939, 209918, -598803, -1402867, -757518, 61031, 177299, 566889, 1359074, 1644766, 947031, -136999, -1489841, -2632243, -2425821, -595377, 600862, -636832, -3460426, -4425749, -2181131, 509409, 1660315, 1333543, 802410, 759666, 1361696, 1657263, 1361461, 1165502, 1189360, 1012681, 296669, -605808, -1535954, -1882710, -858797, 670189, 1040257, 685650, 925446, 1237687, 1263513, 1581050, 2151425, 1551719, -454069, -2269677, -2492568, -1357148, -690234, -1640816, -2317595, -1608591, -520999, 127052, 700204, 1809805, 1685142, -524067, -2869846, -3156061, -1493322, 754894, 2086287, 1940425, 749200, -626354, -1622253, -1996836, -2356801, -1867299, -156139, 1884343, 3331443, 3697680, 3007169, 1797425, 283349, -1371656, -2754032, -3522139, -3032471, -1326818, 545466, 1977755, 2474519, 2032993, 1479049, 1060055, 585345, 287835, 373413, 405405, -85732, -1059029, -2074629, -2601615, -2065327, -460058, 1419926, 2237109, 1589347, -24169, -1168667, -1211382, -1402298, -1748917, -1594633, -759922, 169882, 568726, 261523, -782059, -1333556, -677038, 80933, 291005, -37865, -756721, -987573, -554997, -364850, -403099, 655318, 2589772, 3577803, 3187607, 2068388, 443948, -1358543, -2177326, -1418491, -203105, 543594, 481008, -270151, -738429, -96979, 308988, -145046, -698008, -804799, -866166, -956478, -1184037, -1709390, -1521904, 278765, 2893604, 4142533, 2968820, 532067, -1504890, -2058071, -1910699, -1934254, -1751742, -780126, 675369, 1597128, 1240690, 498360, 135401, -318418, -791651, -405987, 310994, 529931, 562689, 470894, 229284, 28282, -341655, -656739, -434540, 1092, -316864, -1127317, -1603215, -1366881, -295162, 1213289, 2467017, 2463475, 1121901, -472095, -1264861, -1327397, -194879, 1515072, 2397705, 2180082, 1000100, -1455706, -3640353, -3542750, -1505314, 532711, 1201077, 369779, -824328, -809803, 202523, 1043374, 920285, 646394, 1011544, 959421, -27276, -1199734, -1934332, -2024911, -1372033, -419998, -406628, -1230748, -1362900, 28195, 2342140, 3936285, 3516537, 1740934, 127096, -528383, -671594, -685487, -695309, -606055, -871624, -2168908, -2989680, -2485093, -1294105, 210653, 1590750, 2188385, 1714408, 584574, 41189, 417779, 814118, 910360, 779725, 436760, -31776, -567170, -1402666, -2449526, -2761862, -2418352, -1627908, -451521, 777463, 1860163, 2742850, 2564302, 515801, -2351009, -3442812, -1617156, 1226060, 2502339, 1786423, 43063, -1490720, -1999053, -1447359, -793672, -93788, 891788, 2100953, 3335012, 3271878, 1293180, -1304177, -2731256, -2440238, -944707, 835634, 1475619, 403209, -961174, -1530022, -1102635, -252859, 580390, 1501830, 1493906, 527408, -567982, -1122682, -924115, -555668, -411024, -405920, -77783, 8636, -564944, -1022189, -1152014, -1381218, -1194206, -274551, 777031, 1380240, 1207317, 1217357, 1917021, 1805480, 87559, -2171728, -2709000, -1251810, 535778, 1067734, 289352, -701785, -1089819, -568233, 757444, 1865053, 1807322, 1163714, 952812, 1499384, 1596081, 823661, -382244, -1772499, -2655187, -2337032, -947304, 76984, 66542, -249936, -628435, -648474, -545466, -550574, -509514, -125634, 123243, 132631, 166214, 293567, 151288, -3364, 2548, -1407, 740, -325, 49, 143, -284, 389, -469, 531, -580, 618, -649, 673, -692, 707, -719, 728, -735, 740, -743, 744, -745, 744, -743, 741, -738, 735, -731, 727, -722, 717, -711, 706, -700, 694, -687, 681, -674, 667, -660, 653, -646, 638, -631, 623, -616, 608, -600, 592, -585, 577, -569, 561, -552, 544, -536, 528, -520, 511, -503, 495, -486, 478, -470, 461, -453, 444, -436, 427, -418, 410, -401, 393, -384, 375, -366, 358, -349, 340, -331, 322, -314, 305, -296, 287, -278, 269, -260, 251, -242, 233, -224, 215, -206, 196, -187, 178, -169, 160, -150, 141, -132, 122, -113, 104, -94, 85, -75, 66, -56, 47, -37, 28, -18, 9, 0, -10, 19, -29, 39, -49, 58, -68, };


typedef struct audio_reg {
  volatile int control;
  volatile char rarc;
  volatile char ralc;
  volatile char wsrc;
  volatile char wslc;
  volatile int ldata;
  volatile int rdata;
} audio;

void main() {
    audio * const audio_ptr = (audio*)0xFF203040;
    audio_ptr->control = 0b1100;  // set control register to 1100 to clear input and output fifos
    audio_ptr->control = 0x0; // set to zero to allow samples to flow into the fifos

    for (int i = 0; i < (sizeof(left_channel)/sizeof(int)); i++) {
        while (audio_ptr->wslc == 0); // loop if no empty output fifo, wait until there is empty ones
        audio_ptr -> ldata = left_channel[i];
        audio_ptr -> rdata = right_channel[i];
    }

    // printf("%i", sizeof(audio_data));
} 
