using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using LiVEZer.AIMP.LiveControl.Core;
using LiVEZer.AIMP.LiveControl.Core.Actions;

namespace LiVEZer.AIMP.LiveControl.Execution
{

    public class Class1 : AIMPActionEvent
    {
        unsafe public override void HandleEvent(void* data)
        {
            SuperClass.DoIt();
//            MessageBox.Show("Hello from C#");
        }
    }
}
