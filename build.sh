# Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
# 
# This file is part of Dynamo Engine.
# 
# Dynamo Engine is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# Dynamo Engine is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Dynamo Engine.  If not, see <http://www.gnu.org/licenses/>.
#!/usr/bin/env sh

cd Dynamo && make -Bj && cd ..
cd BallisticPotatoes && make -Bj && cd .. && echo "Build complete!"