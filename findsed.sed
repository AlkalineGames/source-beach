#
# copy the first line into hold and start swapping all lines
#
1 {h;d;}; x
$ {p;x;}
#
# remove the empty comment line before the Copyright
#
x
/^[ \t]*\/\/[ \t]*Copyright/ {
  x
  s/^[ \t]*\/\/[ \t]*$//
  s/^\(..*\)$/\1/p
  d
};
x
#
# change license from Apache to MPL
#
/Licensed under the Apache/,/See the License/ D
t
/limitations under the License/,/\/\// c\
\/\/  This Source Code Form is subject to the terms of the Mozilla Public\
\/\/  License, v. 2.0. If a copy of the MPL was not distributed with this\
\/\/  file, You can obtain one at http:\/\/mozilla.org\/MPL\/2.0\/.
t
#
# change "All rights reserved" to MPL
#
/Licensed under the Apache/,/See the License/ D
t
/All rights reserved/ c\
\/\/\
\/\/  This Source Code Form is subject to the terms of the Mozilla Public\
\/\/  License, v. 2.0. If a copy of the MPL was not distributed with this\
\/\/  file, You can obtain one at http:\/\/mozilla.org\/MPL\/2.0\/.
t
#
# change Copyright end date
#
/Copyright \([1-2][0-9][0-9][0-9]\)-\([1-2][0-9][0-9][0-9]\)/ s//Copyright \1-2017/g
#
# replace names
#
/Christopher A\./ s//Christopher/g
/Thames/ s//Augustus/g
/World Fusion (r)/ s//Alkaline Games LLC/g
#
# remove the use of "framework"
#
/ (F|f)rameworks?/ s///g
