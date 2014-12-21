using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
//using LiVEZer.AIMP.LiveControl.Core.Actions;

namespace LiVEZer.AIMP.LiveControl.Core
{

    public static class SuperClass
    {
        public static void DoIt()
        {
            MessageBox.Show("It's from MixedLibrary!", "Mixed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        }
    }
}
