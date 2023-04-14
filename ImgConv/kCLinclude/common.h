/**
 ** This file is part of the ImgConv project.
 ** Copyright 2022-2023 Grégoire BOST <bostgregoire@gmail.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as
 ** published by the Free Software Foundation, either version 3 of the
 ** License, or (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#define X           get_global_id(0)
#define Y           get_global_id(1)
#define _I          ((W * Y + X) * 3)
#define PIX_INDEX   _I
#define INDEX2X     (PIX_INDEX % W)
#define INDEX2Y     (PIX_INDEX / W)
#define OUT_RED     (Out[_I + 0])
#define OUT_GREEN   (Out[_I + 1])
#define OUT_BLUE    (Out[_I + 2])
#define IN_RED      (In[_I + 0])
#define IN_GREEN    (In[_I + 1])
#define IN_BLUE     (In[_I + 2])
