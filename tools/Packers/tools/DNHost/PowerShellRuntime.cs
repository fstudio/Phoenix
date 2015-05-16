//
//
//
using System;
using System.IO;
using System.Diagnostics;
using System.Management.Automation;
using System.Management.Automation.Runspaces;
using System.Collections.ObjectModel;

namespace DNHost{
	public class PowerShellRuntime{
        private String filePath;
        private String mParam;
        public PowerShellRuntime(String scriptFile,String param)
        {
            this.filePath = scriptFile;
            this.mParam = param;
        }
        private Collection<PSObject> Run()
        {
            RunspaceConfiguration runspaceConfiguration = RunspaceConfiguration.Create();
            Runspace runspace = RunspaceFactory.CreateRunspace(runspaceConfiguration);
            runspace.Open();
            RunspaceInvoke scriptInvoker = new RunspaceInvoke(runspace);
            Pipeline pipeline = runspace.CreatePipeline();
            Command scriptCommand = new Command(filePath);
            Collection<CommandParameter> commandParameters = new Collection<CommandParameter>();

            string[] tempParas = mParam.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            for (int i = 0; i < tempParas.Length; i += 2)
            {
                CommandParameter commandParm = new CommandParameter(tempParas[i], tempParas[i + 1]);
                commandParameters.Add(commandParm);
                scriptCommand.Parameters.Add(commandParm);
            }

            pipeline.Commands.Add(scriptCommand);
            Collection<PSObject> psObjects;
            psObjects = pipeline.Invoke();

            if (pipeline.Error.Count > 0)
            {
                throw new Exception("Run PowerShell Script Failed");
            }

            runspace.Close();
            return psObjects;
        }
        /// <summary>
        ///  static int Run()
        /// </summary>
        /// <param name="scriptFile"></param>
        /// <returns></returns>
		public static int Run(String scriptFile,String param){
            if(!File.Exists(scriptFile))
            {
                Console.Write("PowerShell Script File: {} not exists\n", scriptFile);
                return 1;
            }
            PowerShellRuntime psRun = new PowerShellRuntime(scriptFile, param);
            var psObj = psRun.Run();
            Console.Write(psObj.ToString());
            //var ret = psRun.Run();
			return 0;
		}
	}
}