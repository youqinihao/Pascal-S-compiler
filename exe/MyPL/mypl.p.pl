   ******The List Of Pcode******
    0 LDA      0      2        7
    1 LDI      2      2        5
    2 STO     38            
    3 LOD      1      2        5
    4 LDI      2      2        6
    5 STO     38            
    6 LOD      1      2        6
    7 LOD      1      2        7
    8 STO     38            
    9 EXP     32            
   10 LDA      0      2       10
   11 LDC     24      1
   12 STO     38            
   13 LOD      1      2        6
   14 LOD      1      2        7
   15 LSS     47            
   16 JPC     11    140
   17 LDA      0      2        8
   18 LOD      1      2        6
   19 STO     38            
   20 LDA      0      2        9
   21 LOD      1      2        7
   22 LDC     24      1
   23 ADD     52            
   24 STO     38            
   25 LOD      1      2       10
   26 LDC     24      1
   27 EQL     45            
   28 JPC     11    115
   29 LDA      0      2        8
   30 LOD      1      2        8
   31 LDC     24      1
   32 ADD     52            
   33 STO     38            
   34 LOD      1      2        5
   35 LOD      1      2        6
   36 IDX     20      1
   37 LDT     34            
   38 LOD      1      2        5
   39 LOD      1      2        8
   40 IDX     20      1
   41 LDT     34            
   42 GRT     49            
   43 JPC     11     56
   44 LOD      1      2        8
   45 LOD      1      2        7
   46 NEQ     46            
   47 JPC     11     52
   48 LDA      0      2       11
   49 LDC     24      1
   50 STO     38            
   51 JMP     10     55
   52 LDA      0      2       11
   53 LDC     24      0
   54 STO     38            
   55 JMP     10     59
   56 LDA      0      2       11
   57 LDC     24      0
   58 STO     38            
   59 LOD      1      2       11
   60 LDC     24      1
   61 EQL     45            
   62 JPG     12     29
   63 LDA      0      2        9
   64 LOD      1      2        9
   65 LDC     24      1
   66 SUB     53            
   67 STO     38            
   68 LOD      1      2        5
   69 LOD      1      2        6
   70 IDX     20      1
   71 LDT     34            
   72 LOD      1      2        5
   73 LOD      1      2        9
   74 IDX     20      1
   75 LDT     34            
   76 LSS     47            
   77 JPC     11     90
   78 LOD      1      2        9
   79 LOD      1      2        6
   80 NEQ     46            
   81 JPC     11     86
   82 LDA      0      2       11
   83 LDC     24      1
   84 STO     38            
   85 JMP     10     89
   86 LDA      0      2       11
   87 LDC     24      0
   88 STO     38            
   89 JMP     10     93
   90 LDA      0      2       11
   91 LDC     24      0
   92 STO     38            
   93 LOD      1      2       11
   94 LDC     24      1
   95 EQL     45            
   96 JPG     12     63
   97 LOD      1      2        8
   98 LOD      1      2        9
   99 LSS     47            
  100 JPC     11    111
  101 MKS     18     13
  102 LOD      1      2        5
  103 LOD      1      2        8
  104 IDX     20      1
  105 LOD      1      2        5
  106 LOD      1      2        9
  107 IDX     20      1
  108 CAL     19      6
  109 DIS      3      1        2
  110 JMP     10    114
  111 LDA      0      2       10
  112 LDC     24      0
  113 STO     38            
  114 JMP     10     25
  115 MKS     18     13
  116 LOD      1      2        5
  117 LOD      1      2        6
  118 IDX     20      1
  119 LOD      1      2        5
  120 LOD      1      2        9
  121 IDX     20      1
  122 CAL     19      6
  123 DIS      3      1        2
  124 MKS     18     17
  125 LOD      1      2        5
  126 LOD      1      2        6
  127 LOD      1      2        9
  128 LDC     24      1
  129 SUB     53            
  130 CAL     19      7
  131 DIS      3      1        2
  132 MKS     18     17
  133 LOD      1      2        5
  134 LOD      1      2        9
  135 LDC     24      1
  136 ADD     52            
  137 LOD      1      2        7
  138 CAL     19      7
  139 DIS      3      1        2
  140 EXP     32            
  141 MKS     18     17
  142 LOD      1      2        5
  143 LDC     24      1
  144 LOD      1      2        6
  145 CAL     19      7
  146 DIS      3      1        2
  147 EXP     32            
  148 LDC     24     20
  149 WRS     28      0
  150 WRL     63            
  151 LDA      0      1        5
  152 RED     27      1
  153 LDC     24     16
  154 WRS     28     20
  155 WRL     63            
  156 LDA      0      1        6
  157 LDC     24      1
  158 LOD      1      1        5
  159 F1U     14    165
  160 LDA      0      1        8
  161 LOD      1      1        6
  162 IDX     20      1
  163 RED     27      1
  164 F2U     15    160
  165 MKS     18     25
  166 LDA      0      1        8
  167 LOD      1      1        5
  168 CAL     19      6
  169 LDC     24     13
  170 WRS     28     36
  171 WRL     63            
  172 LDA      0      1        7
  173 LDC     24      1
  174 LOD      1      1        5
  175 F1U     14    184
  176 LDA      0      1        8
  177 LOD      1      1        7
  178 IDX     20      1
  179 LDT     34            
  180 WRW     29      1
  181 LDC     24      2
  182 WRS     28     49
  183 F2U     15    176
  184 HLT     31            
