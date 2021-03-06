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
        int m_Collision;

        int m_SpawnX;
        int m_SpawnY;

        int m_CheckPointY;
        int m_CheckPointX;

        int m_AIPositionX;
        int m_AIPositionY;

        string m_triggerEvent;


        public int AIPositionX
        {
            get { return m_AIPositionX; }
            set { m_AIPositionX = value; }
        }

        public int AIPositionY
        {
            get { return m_AIPositionY; }
            set { m_AIPositionY = value; }
        }
        // this a string getter and setter
        public string Triggerevent
        {
            get { return m_triggerEvent; }
            set { m_triggerEvent = value; }
        }

        // This a Checkpoint setter for X and getter for the editor 
        public int CheckPointX
        {
            get { return m_CheckPointX; }
            set { m_CheckPointX = value; }
        }

        // this a Checkpoint setter for Y and getter for the editor 
        public int CheckPointY
        {
            get { return m_CheckPointY; }
            set { m_CheckPointY = value; }
        }

        // this a Checkpoint setter for Y and getter for the editor 
        public int SpawnX
        {
            get { return m_SpawnX; }
            set { m_SpawnX = value; }
        }

        // this a Checkpoint setter for Y and getter for the editor 
        public int SpawnY
        {
            get { return m_SpawnY; }
            set { m_SpawnY = value; }
        }

        // this a Collision Getter and setter 
        public int Collision
        {
            get { return m_Collision; }
            set { m_Collision = value; }
        }

        // PositionX Getter and setter
        public int PositionX
        {
            get { return m_PositionX; }
            set { m_PositionX = value; }
        }

        // PositionY Getter and setter
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
