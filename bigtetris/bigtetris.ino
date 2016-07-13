/*
Copyright 2014 Joel Lienhard  (joel@mclien.de  joel@sisam42.de)

Modified by the Alamance Makers Guild 5/6/2016 (Jeff Wright, Schae Stewart, Danny Oakley)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Need to have e copy of adafruits nepixel Library in the according arduino folder
#include "AMGBigTetris.h"

//
// PLATFORM SPECIFIC
//

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(1));

  setupStrip();
  setupController();
}

//
// END PLATFORM SPECIFIC
//

