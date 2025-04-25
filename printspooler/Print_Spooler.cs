using System;
using System.Runtime.InteropServices;
using System.Text;

class Print_Spooler
    // import useful dlls dynamic linking libraries
    /*
    Dllimport is used to port external driver, like here are using windows spooler drivers
    Charset.auto allows both Unicode and ansi strings, SetLastError is true to get error from Marshal.GetLastWin32Error()
    pPrinterName - name of printer
    IntPtr phPrinter - pointer that will be filled with reference of availabe printer
    OpenPrinter - interface to connect with printer by creating a session, and return a print handle
    pDefault - is for Inptr.Zero which means use system default settings
    */
    [DllImport("winspool.drv", CharSet = CharSet.Auto, SetLastError = true)]
    private static extern bool OpenPrinter(string pPrinterName, out IntPtr phPrinter, IntPtr pDefault);
    
    [DllImport("winspool.drv", SetLastError = true)]
    private static extern bool ClosePrinter(IntPtr hPrinter);
    
    [DllImport("winspool.drv", SetLastError = true)]
    private static extern bool GetPrinter(IntPtr hPrinter, int Level, IntPtr pPrinter, int cbBuf, out int pcbNeeded);
    
    /*
    used to enumerate print jobs in print queue
    hPrinter - reference of open printer handle
    FirstJob - 0th job in queue
    NoJobs - No of jobs
    Level - info level , 1 -> basic info, 2-> more detailed
    pJob - buffer to receive job info structure
    cbBuf - size of buffer in bytes
    pcbNeeded - number of bytes required for buffer
    pcReturned - receives number of job information structures returned

    IntPtr.Zero is nullptr equivalnet in C++
    1. It is used for 2 phase approach to first get the required buffer size
    by making an empty call.
    2. allocate the right size and call again
    */
    [DllImport("winspool.drv", SetLastError = true)]
    private static extern bool EnumJobs(IntPtr hPrinter, int FirstJob, int NoJobs, int Level, 
                                       IntPtr pJob, int cbBuf, out int pcbNeeded, out int pcReturned);

    //Structure for job level 1
    //C# way to structure a layout in memory, sequential makes sure to layout them in similar way as they are in struct
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]      
    private struct JOB_INFO_1
    {
        public int JobId;
        public string pPrinterName;
        public string pMachineName;
        public string pUserName;
        public string pDocument;
        public string pDatatype;
        public string pStatus;
        public int Status;
        public int Priority;
        public int Position;
        public int TotalPages;
        public int PagesPrinted;
        public SYSTEMTIME Submitted;
    }
    [StructLayout(LayoutKind.Sequential)]
    private struct SYSTEMTIME
    {
        public short wYear;
        public short wMonth;
        public short wDayOfWeek;
        public short wDay;
        public short wHour;
        public short wMinute;
        public short wSecond;
        public short wMilliseconds;
    }  
    /*
    Marshal is used to convert C# native DataStructure into Windows api specific datastructures
    */  
    static void Main(string[] args){
        ListPrintJobsUsingWin32Api("Print using something I don't like");
    }  
    static void ListPrintJobsUsingWin32Api(string printerName){
        Console.WriteLine($"print for {printerName} using windows api")
        IntPtr hprinter = IntPtr.Zero;

        // Call with null buffer to get required size
        try
        {
            if(!OpenPrinter(printerName, out hprinter, IntPtr.Zero))
            {
                int error = Marshal.GetLastWin32Error();
                Console.WriteLine($"Error occured: {error}");
                return;
            }
            //get job info
            int cbNeeded = 0;
            int cReturned = 0;
            EnumJobs(hPrinter, 0, 100, 1, IntPtr.Zero, 0, out cbNeeded, out cReturned);//first call
            if (cbNeeded > 0){
                //allocate buffer or spool
                IntPtr pJobInfo = Marshal.AllocHGlobal(cbNeeded);

                //get actual job
                if(EnumJobs(hprinter, 0, 100, 1, pJobInfo, out cbNeeded, out cReturned)){
                    IntPtr currentJob = pJobInfo;
                    for (int i = 0; i < cReturned; i++)
                    {
                        //marshal or convert the data into a struct which C# can understand, by ocnverting memory into struct
                        JOB_INFO_1 jobinfo = (JOB_INFO_1)Marshal.PtrToStructure(currentJob, typeof(JOB_INFO_1));
                        Console.WriteLine($"Job ID: {jobInfo.JobId}");
                        Console.WriteLine($"Document: {jobInfo.pDocument}");
                        Console.WriteLine($"User: {jobInfo.pUserName}");
                        Console.WriteLine($"Status: {jobInfo.pStatus}");

                        //increment
                        currentJob = (IntPtr)((long)currentJob+Marshal.SizeOf(typeof(JOB_INFO_1)));
                    }
                }else{
                    int error = Marshal.GetLastWin32Error();
                    Console.WriteLine($"Failed to get job information. Error code: {error}");
                }
                // Free the allocated memory
                Marshal.FreeHGlobal(pJobInfo);
            }
            else{
                Console.WriteLine("No print jobs found.");
            }

        } 
        catch (Exception ex){
            Console.WriteLine($"Error: {ex.Message}");
        }
        finally{
            // Close the printer handle
            if (hPrinter != IntPtr.Zero)
            {
                ClosePrinter(hPrinter);
            }
        }
    }
}                  