import java.io.*; 
import java.lang.String;
import java.lang.Object;
import java.util.Arrays;
import java.util.*;
import java.text.DecimalFormat;


public class Restore_line
{ 
  public static void main(String[] args)throws Exception 
  { 
  // We need to provide file path as the parameter: 
  // double backquote is to avoid compiler interpret words 
  // like \test as \t (ie. as a escape sequence) 
  

  String st;
  String fileName = "";
  String fileName2= "";
  String fileName3= "";
  String fileName4= "";
  String fileName5= "";
  String fileName6= "";
  String fileName7= "";
  String fileName8= "";
  String benchmark= "";
  int i = 0;
  int cut =262144/256; 
  int section = 5;

  File file_in = new File("inputFile.in"); 
  BufferedReader br_in = new BufferedReader(new FileReader(file_in));
  fileName = br_in.readLine();
  fileName2 = br_in.readLine();
  fileName3 = br_in.readLine();
  fileName4 = br_in.readLine();
  fileName5 = br_in.readLine();
  fileName6 = br_in.readLine();
  fileName7 = br_in.readLine();
  fileName8 = br_in.readLine();
  benchmark = br_in.readLine();

  fileName.replaceAll("\\s+","");
  fileName2.replaceAll("\\s+","");
  fileName3.replaceAll("\\s+","");
  fileName4.replaceAll("\\s+","");
  fileName5.replaceAll("\\s+","");
  fileName6.replaceAll("\\s+","");
  fileName7.replaceAll("\\s+","");
  fileName8.replaceAll("\\s+","");
  benchmark.replaceAll("\\s+","");


  System.out.println("fileName is " + fileName);
  System.out.println("fileName8 is " + benchmark);
  if(args.length == 1)
  {
  	section = Integer.valueOf(args[0]);
  }

  File file = new File(fileName); 
  File file2 = new File(fileName2);
  File file3 = new File(fileName3);
  File file4 = new File(fileName4);
  File file5 = new File(fileName5);
  File file6 = new File(fileName6);
  File file7 = new File(fileName7);
  File file8 = new File(fileName8);

  BufferedReader br = new BufferedReader(new FileReader(file));
  BufferedReader br2 = new BufferedReader(new FileReader(file2));
  BufferedReader br3 = new BufferedReader(new FileReader(file3));
  BufferedReader br4 = new BufferedReader(new FileReader(file4));
  BufferedReader br5 = new BufferedReader(new FileReader(file5));
  BufferedReader br6 = new BufferedReader(new FileReader(file6));
  BufferedReader br7 = new BufferedReader(new FileReader(file7));
  BufferedReader br8 = new BufferedReader(new FileReader(file8)); 
  



  ArrayList<Integer> data = new ArrayList<Integer>();
  ArrayList<Double> data1 = new ArrayList<Double>();
  ArrayList<Double> data2 = new ArrayList<Double>();
  ArrayList<Double> data3 = new ArrayList<Double>();
  ArrayList<Double> data4 = new ArrayList<Double>();
  ArrayList<Double> data5 = new ArrayList<Double>();
  ArrayList<Double> data6 = new ArrayList<Double>();
  ArrayList<Double> data7 = new ArrayList<Double>();
  ArrayList<Double> data8 = new ArrayList<Double>();
  //String [] words = new String[2];


  ArrayList<Double> out_data2 = new ArrayList<Double>();
  ArrayList<Double> out_data3 = new ArrayList<Double>();
  ArrayList<Double> out_data4 = new ArrayList<Double>();
  ArrayList<Double> out_data5 = new ArrayList<Double>();
  ArrayList<Double> out_data6 = new ArrayList<Double>();
  ArrayList<Double> out_data7 = new ArrayList<Double>();
  ArrayList<Double> out_data8 = new ArrayList<Double>();

  FileWriter fileWriter2 = new FileWriter(benchmark+"_"+Integer.toString(section)+"line_restored_10.out",false);
  FileWriter fileWriter3 = new FileWriter(benchmark+"_"+Integer.toString(section)+"line_restored_25.out",false);
  FileWriter fileWriter4 = new FileWriter(benchmark+"_"+Integer.toString(section)+"line_restored_40.out",false);
  FileWriter fileWriter5 = new FileWriter(benchmark+"_"+Integer.toString(section)+"line_restored_50.out",false);
  FileWriter fileWriter6 = new FileWriter(benchmark+"_"+Integer.toString(section)+"line_restored_60.out",false);
  FileWriter fileWriter7 = new FileWriter(benchmark+"_"+Integer.toString(section)+"line_restored_drop.out",false);
  FileWriter fileWriter8 = new FileWriter(benchmark+"_"+Integer.toString(section)+"line_restored_90.out",false);
  FileWriter fileWriter9 = new FileWriter(benchmark+"_"+Integer.toString(section)+"line_error_report.txt",false);

  int len_data1 = Restore_2.readInput(br, data, data1, cut);
  int len_data2 = Restore_2.readInput(br2, data2, cut);
  int len_data3 = Restore_2.readInput(br3, data3, cut);
  int len_data4 = Restore_2.readInput(br4, data4, cut);
  int len_data5 = Restore_2.readInput(br5, data5, cut);
  int len_data6 = Restore_2.readInput(br6, data6, cut);
  int len_data7 = Restore_2.readInput(br7, data7, cut);
  int len_data8 = Restore_2.readInput(br8, data8, cut);
  

/*

   System.out.println(data3.get(1));
   System.out.println(data4.get(1));
   System.out.println(data5.get(1));
   System.out.println(data6.get(1));
   System.out.println(data7.get(1));
   System.out.println(data8.get(0));
*/

   int length = Math.min(len_data1,Math.min(len_data2,Math.min(len_data3,Math.min(len_data4,Math.min(len_data5,Math.min(len_data6,Math.min(len_data7,len_data8)))))));
   
                                     
   System.out.println(data8.size());
   System.out.println(data7.size());
   System.out.println(data6.size());
   System.out.println(data5.size());
   System.out.println(data4.size());
   System.out.println(data3.size());
   System.out.println(data2.size());
   System.out.println(data1.size());
   System.out.println(data.size());
   System.out.println(length);
	


   double [] abs_error2 = new double [length];
   double [] abs_error3 = new double [length];
   double [] abs_error4 = new double [length];
   double [] abs_error5 = new double [length];
   double [] abs_error6 = new double [length];
   double [] abs_error7 = new double [length];
   double [] abs_error8 = new double [length];

   double [] relative_error2 = new double [length];
   double [] relative_error3 = new double [length];
   double [] relative_error4 = new double [length];
   double [] relative_error5 = new double [length];
   double [] relative_error6 = new double [length];
   double [] relative_error7 = new double [length];
   double [] relative_error8 = new double [length];

   //System.out.println(length+"  "+(length/5)); 

	
	int len_out_data2 = Restore_line.restoreData_line( out_data2, data1, length, section);
	int len_out_data3 = Restore_line.restoreData_line( out_data3, data1, length, section);
	int len_out_data4 = Restore_line.restoreData_line( out_data4, data1, length, section);
	int len_out_data5 = Restore_line.restoreData_line( out_data5, data1, length, section);
	int len_out_data6 = Restore_line.restoreData_line( out_data6, data1, length, section);
	int len_out_data7 = Restore_line.restoreData_line( out_data7, data1, length, section);
	int len_out_data8 = Restore_line.restoreData_line( out_data8, data1, length, section);

	int out_data_length = Math.min(length,Math.min(len_out_data2,Math.min(len_data3,Math.min(len_data4,Math.min(len_data5,Math.min(len_data6,Math.min(len_data7,len_data8)))))));

  /*
   System.out.println(len_out_data2);
   System.out.println(len_out_data3);
   System.out.println(len_out_data4);
   System.out.println(len_out_data5);
   System.out.println(len_out_data6);
   System.out.println(len_out_data7);
   System.out.println(len_out_data8);
*/

    fileWriter2.write("cache_lines,MRC\n");
    fileWriter3.write("cache_lines,MRC\n");
    fileWriter4.write("cache_lines,MRC\n");
    fileWriter5.write("cache_lines,MRC\n");
    fileWriter6.write("cache_lines,MRC\n");
    fileWriter7.write("cache_lines,MRC\n");
    fileWriter8.write("cache_lines,MRC\n");


   for(int j = 0; j < out_data_length; j++)
   {
      
      fileWriter2.write(data.get(j)+","+out_data2.get(j)+"\n");
      fileWriter3.write(data.get(j)+","+out_data3.get(j)+"\n");
      fileWriter4.write(data.get(j)+","+out_data4.get(j)+"\n");
      fileWriter5.write(data.get(j)+","+out_data5.get(j)+"\n");
      fileWriter6.write(data.get(j)+","+out_data6.get(j)+"\n");
      fileWriter7.write(data.get(j)+","+out_data7.get(j)+"\n");
      fileWriter8.write(data.get(j)+","+out_data8.get(j)+"\n");

      abs_error2[j]= Math.abs(data1.get(j)-out_data2.get(j));
      abs_error3[j]= Math.abs(data1.get(j)-out_data3.get(j));
      abs_error4[j]= Math.abs(data1.get(j)-out_data4.get(j));
      abs_error5[j]= Math.abs(data1.get(j)-out_data5.get(j));
      abs_error6[j]= Math.abs(data1.get(j)-out_data6.get(j));
      abs_error7[j]= Math.abs(data1.get(j)-out_data7.get(j));
      abs_error8[j]= Math.abs(data1.get(j)-out_data8.get(j));
      
      relative_error2[j]= Math.abs(data1.get(j)-out_data2.get(j))/data1.get(j);
      relative_error3[j]= Math.abs(data1.get(j)-out_data3.get(j))/data1.get(j);
      relative_error4[j]= Math.abs(data1.get(j)-out_data4.get(j))/data1.get(j);
      relative_error5[j]= Math.abs(data1.get(j)-out_data5.get(j))/data1.get(j);
      relative_error6[j]= Math.abs(data1.get(j)-out_data6.get(j))/data1.get(j);
      relative_error7[j]= Math.abs(data1.get(j)-out_data7.get(j))/data1.get(j);
      relative_error8[j]= Math.abs(data1.get(j)-out_data8.get(j))/data1.get(j);



   }

   double ave_abs_error2 = 0;
   double ave_abs_error3 = 0;
   double ave_abs_error4 = 0;
   double ave_abs_error5 = 0;
   double ave_abs_error6 = 0;
   double ave_abs_error7 = 0;
   double ave_abs_error8 = 0;

   double ave_relative_error2 = 0;
   double ave_relative_error3 = 0;
   double ave_relative_error4 = 0;
   double ave_relative_error5 = 0;
   double ave_relative_error6 = 0;
   double ave_relative_error7 = 0;
   double ave_relative_error8 = 0;

   for(int j = 0; j < out_data_length; j++)
   {
      ave_relative_error2 += relative_error2[j];
      ave_relative_error3 += relative_error3[j];
      ave_relative_error4 += relative_error4[j];
      ave_relative_error5 += relative_error5[j];
      ave_relative_error6 += relative_error6[j];
      ave_relative_error7 += relative_error7[j];
      ave_relative_error8 += relative_error8[j]; 

      ave_abs_error2 += abs_error2[j];
      ave_abs_error3 += abs_error3[j];
      ave_abs_error4 += abs_error4[j];
      ave_abs_error5 += abs_error5[j];
      ave_abs_error6 += abs_error6[j];
      ave_abs_error7 += abs_error7[j];
      ave_abs_error8 += abs_error8[j];
   }

   ave_abs_error2 = ave_abs_error2/length;
   ave_abs_error3 = ave_abs_error3/length;
   ave_abs_error4 = ave_abs_error4/length;
   ave_abs_error5 = ave_abs_error5/length;
   ave_abs_error6 = ave_abs_error6/length;
   ave_abs_error7 = ave_abs_error7/length;
   ave_abs_error8 = ave_abs_error8/length;

   ave_relative_error2 = ave_relative_error2/length; 
   ave_relative_error3 = ave_relative_error3/length;
   ave_relative_error4 = ave_relative_error4/length; 
   ave_relative_error5 = ave_relative_error5/length;
   ave_relative_error6 = ave_relative_error6/length;
   ave_relative_error7 = ave_relative_error7/length;
   ave_relative_error8 = ave_relative_error8/length; 

   DecimalFormat df = new DecimalFormat("#.###");
   fileWriter9.write("drop_rate,abs_err,relative_err\n");
   fileWriter9.write("10,"+df.format(ave_abs_error2)+","+df.format(ave_relative_error2)+"\n");
   fileWriter9.write("25,"+df.format(ave_abs_error3)+","+df.format(ave_relative_error3)+"\n");
   fileWriter9.write("40,"+df.format(ave_abs_error4)+","+df.format(ave_relative_error4)+"\n");
   fileWriter9.write("50,"+df.format(ave_abs_error5)+","+df.format(ave_relative_error5)+"\n");
   fileWriter9.write("60,"+df.format(ave_abs_error6)+","+df.format(ave_relative_error6)+"\n");
   fileWriter9.write("drop,"+df.format(ave_abs_error7)+","+df.format(ave_relative_error7)+"\n");
   fileWriter9.write("90,"+df.format(ave_abs_error8)+","+df.format(ave_relative_error8)+"\n");


   fileWriter2.close();
   fileWriter3.close();
   fileWriter4.close();
   fileWriter5.close();
   fileWriter6.close();
   fileWriter7.close();
   fileWriter8.close();
   fileWriter9.close();

  } 


  public static int readInput(BufferedReader br, ArrayList<Integer> data, ArrayList<Double> data1, int cut)
/* read from file, write into ArrayList, the limitation of maximum number to read is cut.
*/ 
{
	int i = 0;
	String st;
	try{
		while ((st = br.readLine()) != null) 
		{
			if(i==0)
			{
				i++;
				continue;
			}
			String [] words = st.split(",");

			data.add(Integer.parseInt(words[0]));
			data1.add(Double.parseDouble(words[1])); 
			i++;
			if(i == cut) break;
		}
	}catch(IOException e) {
		e.printStackTrace();
	}



	return data1.size();

}


public static int readInput(BufferedReader br, ArrayList<Double> data1, int cut)
{
	int i = 0;
	String st;
	try{
		while ((st = br.readLine()) != null) 
		{
			if(i==0)
			{
				i++;
				continue;
			}
			String [] words = st.split(",");

			data1.add(Double.parseDouble(words[1])); 
			i++;
			if(i == cut) break;
		}
	}catch(IOException e) {
		e.printStackTrace();
	}
	

	return data1.size();
}

public static int restoreData(ArrayList<Double> data2, ArrayList<Double> out_data2,ArrayList<Double> data1, int length, int section)
{


	for(int k = 0; k < section; k++)
	{

		int len_segment = length/section;
    int seg_start = len_segment * k;
    int seg_end = len_segment * (k+1) ;
    Double diff2 = (Double) data2.get(seg_start) - data2.get(seg_end); 
    Double diff1 = (Double) data1.get(seg_start) - data1.get(seg_end);

		for(int j = seg_start; j < seg_end; j++)
		{
      Double diff = (data2.get(seg_start) - data2.get(j))*diff1/diff2;
			out_data2.add(j,(data1.get(seg_start) - diff)); 
	     
  	
		}
	}

	return out_data2.size();
}

public static int restoreData_line(ArrayList<Double> out_data2,ArrayList<Double> data1, int length, int section)
{

  for(int k = 0; k < section; k++)
  {

    int len_segment = length/section;
    int seg_start = len_segment * k;
    int seg_end = len_segment * (k+1) ;
    Double point1 = (Double) data1.get(seg_start);
    Double point2 = (Double) data1.get(seg_end);
    Double diff = point1 - point2;
    Double seg_increment = diff/len_segment;

    int jj = 0;
    for(int j = seg_start; j < seg_end; j++)
    {
      out_data2.add(j,(point1 + jj* seg_increment)); 
      jj++; 
    
    }
  }

  return out_data2.size();

}


} 