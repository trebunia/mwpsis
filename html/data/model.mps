* Problem:    model
* Class:      MIP
* Rows:       9
* Columns:    12 (12 integer, 0 binary)
* Non-zeros:  72
* Format:     Fixed MPS
*
NAME          model
ROWS
 N  z
 L  c1
 L  c2
 L  c3
 L  c4
 G  c5
 L  c6
 G  c7
 G  c8
COLUMNS
    M0000001  'MARKER'                 'INTORG'
    X[1,1]    z                32000   c1                   1
    X[1,1]    c5                8000   c6                8000
    X[1,1]    c7                 -10   c8                 700
    X[1,2]    z                24000   c2                   1
    X[1,2]    c5                6000   c6                6000
    X[1,2]    c7                 -10   c8                 700
    X[1,3]    z                12000   c3                   1
    X[1,3]    c5                1000   c6                1000
    X[1,3]    c7                 275   c8                3300
    X[1,4]    z                 6000   c4                   1
    X[1,4]    c5                 500   c6                 500
    X[1,4]    c7                 275   c8                3300
    X[5,1]    z                 6400   c1                   1
    X[5,1]    c5               56000   c6               56000
    X[5,1]    c7                  80   c8                 600
    X[5,2]    z                 4800   c2                   1
    X[5,2]    c5               42000   c6               42000
    X[5,2]    c7                  80   c8                 600
    X[5,3]    z                 6400   c3                   1
    X[5,3]    c5                7000   c6                7000
    X[5,3]    c7                 650   c8                2875
    X[5,4]    z                 3200   c4                   1
    X[5,4]    c5                3500   c6                3500
    X[5,4]    c7                 650   c8                2875
    X[6,1]    z                19200   c1                   1
    X[6,1]    c5               48000   c6               48000
    X[6,1]    c7                19.7   c8                 500
    X[6,2]    z                14400   c2                   1
    X[6,2]    c5               36000   c6               36000
    X[6,2]    c7                19.7   c8                 500
    X[6,3]    z                 8800   c3                   1
    X[6,3]    c5                6000   c6                6000
    X[6,3]    c7              398.75   c8                2450
    X[6,4]    z                 4400   c4                   1
    X[6,4]    c5                3000   c6                3000
    X[6,4]    c7              398.75   c8                2450
    M0000002  'MARKER'                 'INTEND'
RHS
    RHS1      c1                1875   c2                3750
    RHS1      c3                1250   c4                2500
    RHS1      c5              500000   c6              500500
BOUNDS
 PL BND1      X[1,1]  
 PL BND1      X[1,2]  
 PL BND1      X[1,3]  
 PL BND1      X[1,4]  
 PL BND1      X[5,1]  
 PL BND1      X[5,2]  
 PL BND1      X[5,3]  
 PL BND1      X[5,4]  
 PL BND1      X[6,1]  
 PL BND1      X[6,2]  
 PL BND1      X[6,3]  
 PL BND1      X[6,4]  
ENDATA
