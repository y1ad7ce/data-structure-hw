HOMEWORK 2: SCHEDULE CLASSES

References:

http://www.cplusplus.com/doc/tutorial/arrays/
https://stackoverflow.com/questions/22521536/why-am-i-getting-linker-command-failed-with-exit-code-1
https://stackoverflow.com/questions/20833708/c-linker-error
https://stackoverflow.com/questions/1124634/call-destructor-and-then-constructor-resetting-an-object
http://www.cplusplus.com/reference/iomanip/setw/
https://stackoverflow.com/questions/14783665/there-is-an-error-shows-up-to-be-comparison-between-pointer-and-integer-int
https://stackoverflow.com/questions/905479/stdstring-length-and-size-member-functions
https://stackoverflow.com/questions/2596953/multiply-char-by-integer-c 
http://www.cplusplus.com/reference/string/stoi/
http://www.cplusplus.com/reference/string/stof/
http://www.cplusplus.com/reference/string/string/substr/
https://www.geeksforgeeks.org/converting-strings-numbers-cc/
https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
https://stackoverflow.com/questions/30814618/no-matching-function-for-call-to-sort


https://stackoverflow.com/questions/2390912/checking-for-an-empty-file-in-c
https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector


Test case:

Input:
648 interdisc 19sdf2 THE_GENOME_AND_YOU MR 02:00PM 03:50PM Sage_Dining_Hall
62409 1337 12fwefwef5 DATA_STRUCTURES WR 02:00PM 03:50PM Sage_Dining_Hall
616 chemistry 11aaa-05 DATA_STRUCTURES_IN_CHEMISTRY T 11:00AM 11:50AM TBA
6348300 1337 14213 FOUNDATIONS_OF_NONSENSE MR 10:00AM 11:50AM Sage_Dining_Hall
72 chemistry 161234as MATERIALS_SCIENCE MW 01:00PM 01:50PM RCKTTS_2111111111
63765 1337 1 ADS12223 MTWRF 06:00PM 07:50PM DARRIN_008
64620 earth_science 21 STRUCTURAL_GEOLOGY RF 04:00PM 05:50PM J-ROWL_3QQQ
63893 chemistry 31 PHYSICS_I R 04:00PM 04:50PM TBA
63108 biomistry 51 PHYSICS_I TF 10:00AM 11:20AM DARRIN_CS
62562 biomistry ABCD ADVANSED_AMERICAN_POLITICS_IN_NONSENSE W 02:00AM 08:50AM Sage_Dining_Hall
63895 chemistry 1100-18 ADVANSED_AMERICAN_POLITICS_IN_NONSENSE T 05:00PM 10:50PM Sage_Dining_Hall
63894 biomistry 1100-17 AMERICAN_MYSTERY R 04:00PM 04:50PM TBA
639a a_study 1290-01 AMERICAN_POLITICS_IN_NONSENSE MR 10:00AM 11:50AM Sage_Dining_Hall
631re biomistry 1100-04 PUBLIC_SPEAKING R 10:00AM 10:50AM TBA
6 biomistry 1100-09 CHEATING_PSYCHOLOGY M 02:00PM 04:50PM WALKER_IN_SNOW
as564 computer_study 1110-03 AMERICAN_POLITICS_IN_NONSENSE MW 03:00PM 10:50PM Sage_Dining_Hall

Output:

1.Room:

Room DARRIN_008
Dept  Coursenum  Class Title  Day        Start Time  End Time
----  ---------  -----------  ---------  ----------  --------
1337  1          ADS12223     Monday     06:00PM     07:50PM 
1337  1          ADS12223     Tuesday    06:00PM     07:50PM 
1337  1          ADS12223     Wednesday  06:00PM     07:50PM 
1337  1          ADS12223     Thursday   06:00PM     07:50PM 
1337  1          ADS12223     Friday     06:00PM     07:50PM 
5 entries

Room DARRIN_CS
Dept       Coursenum  Class Title  Day      Start Time  End Time
---------  ---------  -----------  -------  ----------  --------
biomistry  51         PHYSICS_I    Tuesday  10:00AM     11:20AM 
biomistry  51         PHYSICS_I    Friday   10:00AM     11:20AM 
2 entries

Room J-ROWL_3QQQ
Dept           Coursenum  Class Title         Day       Start Time  End Time
-------------  ---------  ------------------  --------  ----------  --------
earth_science  21         STRUCTURAL_GEOLOGY  Thursday  04:00PM     05:50PM 
earth_science  21         STRUCTURAL_GEOLOGY  Friday    04:00PM     05:50PM 
2 entries

Room RCKTTS_2111111111
Dept       Coursenum  Class Title        Day        Start Time  End Time
---------  ---------  -----------------  ---------  ----------  --------
chemistry  161234as   MATERIALS_SCIENCE  Monday     01:00PM     01:50PM 
chemistry  161234as   MATERIALS_SCIENCE  Wednesday  01:00PM     01:50PM 
2 entries

Room Sage_Dining_Hall
Dept            Coursenum   Class Title                             Day        Start Time  End Time
--------------  ----------  --------------------------------------  ---------  ----------  --------
a_study         1290-01     AMERICAN_POLITICS_IN_NONSENSE           Monday     10:00AM     11:50AM 
1337            14213       FOUNDATIONS_OF_NONSENSE                 Monday     10:00AM     11:50AM 
interdisc       19sdf2      THE_GENOME_AND_YOU                      Monday     02:00PM     03:50PM 
computer_study  1110-03     AMERICAN_POLITICS_IN_NONSENSE           Monday     03:00PM     10:50PM 
chemistry       1100-18     ADVANSED_AMERICAN_POLITICS_IN_NONSENSE  Tuesday    05:00PM     10:50PM 
biomistry       ABCD        ADVANSED_AMERICAN_POLITICS_IN_NONSENSE  Wednesday  02:00AM     08:50AM 
1337            12fwefwef5  DATA_STRUCTURES                         Wednesday  02:00PM     03:50PM 
computer_study  1110-03     AMERICAN_POLITICS_IN_NONSENSE           Wednesday  03:00PM     10:50PM 
a_study         1290-01     AMERICAN_POLITICS_IN_NONSENSE           Thursday   10:00AM     11:50AM 
1337            14213       FOUNDATIONS_OF_NONSENSE                 Thursday   10:00AM     11:50AM 
1337            12fwefwef5  DATA_STRUCTURES                         Thursday   02:00PM     03:50PM 
interdisc       19sdf2      THE_GENOME_AND_YOU                      Thursday   02:00PM     03:50PM 
12 entries

Room TBA
Dept       Coursenum  Class Title                   Day       Start Time  End Time
---------  ---------  ----------------------------  --------  ----------  --------
chemistry  11aaa-05   DATA_STRUCTURES_IN_CHEMISTRY  Tuesday   11:00AM     11:50AM 
biomistry  1100-04    PUBLIC_SPEAKING               Thursday  10:00AM     10:50AM 
biomistry  1100-17    AMERICAN_MYSTERY              Thursday  04:00PM     04:50PM 
chemistry  31         PHYSICS_I                     Thursday  04:00PM     04:50PM 
4 entries

Room WALKER_IN_SNOW
Dept       Coursenum  Class Title          Day     Start Time  End Time
---------  ---------  -------------------  ------  ----------  --------
biomistry  1100-09    CHEATING_PSYCHOLOGY  Monday  02:00PM     04:50PM 
1 entry



2. Department:

1. dept biomistry:

Dept biomistry
Coursenum  Class Title                             Day        Start Time  End Time
---------  --------------------------------------  ---------  ----------  --------
1100-04    PUBLIC_SPEAKING                         Thursday   10:00AM     10:50AM 
1100-09    CHEATING_PSYCHOLOGY                     Monday     02:00PM     04:50PM 
1100-17    AMERICAN_MYSTERY                        Thursday   04:00PM     04:50PM 
51         PHYSICS_I                               Tuesday    10:00AM     11:20AM 
51         PHYSICS_I                               Friday     10:00AM     11:20AM 
ABCD       ADVANSED_AMERICAN_POLITICS_IN_NONSENSE  Wednesday  02:00AM     08:50AM 
6 entries

2. dept rpi:

No data available.


3. Custom:

Ranking for class time: 

1: AMERICAN_POLITICS_IN_NONSENSE
 ==>19 hour(s) and 20 mintue(s) in weekly total.

2: ADVANSED_AMERICAN_POLITICS_IN_NONSENSE
 ==>12 hour(s) and 40 mintue(s) in weekly total.

3: ADS12223
 ==>9 hour(s) and 10 mintue(s) in weekly total.

4: DATA_STRUCTURES
 ==>3 hour(s) and 40 mintue(s) in weekly total.

5: FOUNDATIONS_OF_NONSENSE
 ==>3 hour(s) and 40 mintue(s) in weekly total.

6: STRUCTURAL_GEOLOGY
 ==>3 hour(s) and 40 mintue(s) in weekly total.

7: THE_GENOME_AND_YOU
 ==>3 hour(s) and 40 mintue(s) in weekly total.

8: PHYSICS_I
 ==>3 hour(s) and 30 mintue(s) in weekly total.

9: CHEATING_PSYCHOLOGY
 ==>2 hour(s) and 50 mintue(s) in weekly total.

10: MATERIALS_SCIENCE
 ==>1 hour(s) and 40 mintue(s) in weekly total.

11: AMERICAN_MYSTERY
 ==>0 hour(s) and 50 mintue(s) in weekly total.

12: DATA_STRUCTURES_IN_CHEMISTRY
 ==>0 hour(s) and 50 mintue(s) in weekly total.

13: PUBLIC_SPEAKING
 ==>0 hour(s) and 50 mintue(s) in weekly total.

