﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StructByLightningsTileEditor
{
    class TIleClass
    {

        int m_PositionX;
        int m_PositionY;
        int ID = 0;

       

        public int PositionX
        {
            get { return m_PositionX; }
            set { m_PositionX = value; }
        }

        public int PositionY
        {
            get { return m_PositionY; }
            set { m_PositionY = value; }
        }

        public int m_ID
        {
            get { return ID; }
            set { ID = value; }
        }
        public TIleClass(int x, int y)
        {
            this.m_PositionX = x;
            this.m_PositionY = y;
        }

    }
}
