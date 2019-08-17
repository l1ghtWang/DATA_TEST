import java.io.*; 
import java.lang.String;
import java.lang.Object;
import java.util.Arrays;
import java.util.*;

public class Restore
{ 
  public static void main(String[] args)throws Exception 
  { 
  // We need to provide file path as the parameter: 
  // double backquote is to avoid compiler interpret words 
  // like \test as \t (ie. as a escape sequence) 
  File file = new File("AET_PIN_cactusADM_AUG13.out");
  File file2 = new File("AET_PIN_DROP_10_cactusADM_JAN22.out");
  File file3 = new File("AET_PIN_DROP_25_cactusADM_AUG13.out");
  File file4 = new File("AET_PIN_DROP_40_cactusADM_JAN22.out");
  File file5 = new File("AET_PIN_DROP_50_cactusADM_AUG13.out");
  File file6 = new File("AET_PIN_DROP_60_cactusADM_JAN22.out");
  File file7 = new File("AET_PIN_DROP_cactusADM_AUG13.out");
  File file8 = new File("AET_PIN_DROP_90_cactusADM_JAN22.out");

  String st;
  int i = 0;
  int cut =262144/256; 
  int section = 5;
  if(args.length == 1) section = Integer.valueOf(args[0]);
  String benchmark = "cactusADM";

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

  FileWriter fileWriter2 = new FileWriter(benchmark+"_"+Integer.toString(section)+"section_restored_10.out",false);
  FileWriter fileWriter3 = new FileWriter(benchmark+"_"+Integer.toString(section)+"section_restored_25.out",false);
  FileWriter fileWriter4 = new FileWriter(benchmark+"_"+Integer.toString(section)+"section_restored_40.out",false);
  FileWriter fileWriter5 = new FileWriter(benchmark+"_"+Integer.toString(section)+"section_restored_50.out",false);
  FileWriter fileWriter6 = new FileWriter(benchmark+"_"+Integer.toString(section)+"section_restored_60.out",false);
  FileWriter fileWriter7 = new FileWriter(benchmark+"_"+Integer.toString(section)+"section_restored_drop.out",false);
  FileWriter fileWriter8 = new FileWriter(benchmark+"_"+Integer.toString(section)+"section_restored_90.out",false);
  FileWriter fileWriter9 = new FileWriter(benchmark+"_"+Integer.toString(section)+"section_error_report.txt",false);

  i = 0;
  while ((st = br.readLine()) != null) 
  {
  	if(i==0)
  	{
  		i++;
  		continue;
	}
  	//System.out.println("1\n");
  	String [] words = st.split(",");
  	//System.out.println(st);
    //System.out.println(words[0]+" "+words[1]);

    data.add(Integer.parseInt(words[0]));
    data1.add(Double.parseDouble(words[1])); 
    i++;
    if(i == cut) break;
   }


  i = 0;
  while ((st = br2.readLine()) != null) 
  {
  	if(i==0)
  	{
  		i++;
  		continue;
	  }
  	//System.out.println("1\n");
  	String [] words = st.split(",");
  	//System.out.println(st);
    //System.out.println(words[0]+" "+words[1]);

    data2.add(Double.parseDouble(words[1])); 
    i++;
    if(i == cut) break;

   }

  i = 0;
  while ((st = br3.readLine()) != null) 
  {
  	if(i==0)
  	{
  		i++;
  		continue;
	  }
  
  	String [] words = st.split(",");
  	data3.add(Double.parseDouble(words[1])); 
    i++;
    if(i == cut) break;
  }

  i = 0;
  while ((st = br4.readLine()) != null) 
  {
  	if(i==0)
  	{
  		i++;
  		continue;
	  }
  
  	String [] words = st.split(",");
  	data4.add(Double.parseDouble(words[1])); 

    i++;
    if(i == cut) break; 	
   }

  i = 0;
  while ((st = br5.readLine()) != null) 
  {
  	if(i==0)
  	{
  		i++;
  		continue;
	  }
  
  	String [] words = st.split(",");
  	data5.add(Double.parseDouble(words[1])); 

  	i++;
    if(i == cut) break;
   }

   i = 0;
   while ((st = br6.readLine()) != null) 
  {
  	if(i==0)
  	{
  		i++;
  		continue;
	  }
  
  	String [] words = st.split(",");
  	data6.add(Double.parseDouble(words[1])); 
  	i++;
    if(i == cut) break;

   }

  i = 0;
  while ((st = br7.readLine()) != null) 
  {
  	if(i==0)
  	{
  		i++;
  		continue;
	  }
  
  	String [] words = st.split(",");
  	data7.add(Double.parseDouble(words[1])); 
  	i++;
    if(i == cut) break;

   }


  i = 0;
  while ((st = br8.readLine()) != null) 
  {
  	if(i==0)
  	{
  		i++;
  		continue;
	  }
  
  	String [] words = st.split(",");
  	data8.add(Double.parseDouble(words[1])); 
  	i++;
    if(i == cut) break;

   }


   /*
   System.out.println(data3.get(1));
   System.out.println(data4.get(1));
   System.out.println(data5.get(1));
   System.out.println(data6.get(1));
   System.out.println(data7.get(1));
   System.out.println(data8.get(0));


   
   System.out.println(cut);
   System.out.println(data7.size());
   System.out.println(data6.size());
   System.out.println(data5.size());
   System.out.println(data4.size());
   System.out.println(data3.size());
   System.out.println(data2.size());
   System.out.println(data1.size());
   System.out.println(data.size());
	 /**/
   //System.out.println("9999");

   int length = Math.min(data.size(),Math.min(data1.size(),Math.min(data2.size(),Math.min(data3.size(),Math.min(data4.size(),Math.min(data5.size(),Math.min(data6.size(),data7.size())))))));


   //System.out.println("888");
      //System.out.println("1111 "+length);

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

   int count = 0;
   int countMin = 0;
   for(int k = 0; k < section; k++)
   {

        for(int j = length/section*k; j < length/section*(k+1); j++)
        {
          //System.out.println(length*(1/5));
          int mean = length/section/2*(1+2*k);
          //System.out.println(mean);
          Double diff = data2.get(mean) - data1.get(mean); 
          //System.out.println(data2.get(j));
          out_data2.add(j,(data2.get(j) - diff)); 
          count++;
        }
   }
   countMin = count;


   count = 0;

   for(int k = 0; k < section; k++)
   {

        for(int j = length/section*k; j < length/section*(k+1); j++)
        {
          //System.out.println(length*(1/5));
          int mean = length/section/2*(1+2*k);
          //System.out.println(mean);
          Double diff = data3.get(mean) - data1.get(mean); 
          //System.out.println(data2.get(j));
          out_data3.add(j,(data3.get(j) - diff)); 
          count++;

        }
   }
   countMin = Math.min(countMin,count);
   count = 0;

   for(int k = 0; k < section; k++)
   {

        for(int j = length/section*k; j < length/section*(k+1); j++)
        {
          //System.out.println(length*(1/5));
          int mean = length/section/2*(1+2*k);
          //System.out.println(mean);
          Double diff = data4.get(mean) - data1.get(mean); 
          //System.out.println(data2.get(j));
          out_data4.add(j,(data4.get(j) - diff)); 
          count++;

        }
   }
  countMin = Math.min(countMin,count);
   count = 0;

   for(int k = 0; k < section; k++)
   {

        for(int j = length/section*k; j < length/section*(k+1); j++)
        {
          //System.out.println(length*(1/5));
          int mean = length/section/2*(1+2*k);
          //System.out.println(mean);
          Double diff = data5.get(mean) - data1.get(mean); 
          //System.out.println(data2.get(j));
          out_data5.add(j,(data5.get(j) - diff)); 
          count++;

        }
   }

   countMin = Math.min(countMin,count);
   count = 0;
    for(int k = 0; k < section; k++)
   {

        for(int j = length/section*k; j < length/section*(k+1); j++)
        {
          //System.out.println(length*(1/5));
          int mean = length/section/2*(1+2*k);
          //System.out.println(mean);
          Double diff = data6.get(mean) - data1.get(mean); 
          //System.out.println(data2.get(j));
          out_data6.add(j,(data6.get(j) - diff)); 
          count++;

        }
   }
   countMin = Math.min(countMin,count);
   count = 0;
   for(int k = 0; k < section; k++)
   {

        for(int j = length/section*k; j < length/section*(k+1); j++)
        {
          //System.out.println(length*(1/5));
          int mean = length/section/2*(1+2*k);
          //System.out.println(mean);
          Double diff = data7.get(mean) - data1.get(mean); 
          //System.out.println(data2.get(j));
          out_data7.add(j,(data7.get(j) - diff)); 
          count++;

        }
   }

   countMin = Math.min(countMin,count);
   count = 0;

   for(int k = 0; k < section; k++)
   {

        for(int j = length/section*k; j < length/section*(k+1); j++)
        {
          //System.out.println(length*(1/5));
          int mean = length/section/2*(1+2*k);
          //System.out.println(mean);
          Double diff = data8.get(mean) - data1.get(mean); 
          //System.out.println(data2.get(j));
          out_data8.add(j,(data8.get(j) - diff)); 
          //System.out.println(out_data8.get(j));
          count = j;

        }
   }


    fileWriter2.write("cache_lines,MRC\n");
    fileWriter3.write("cache_lines,MRC\n");
    fileWriter4.write("cache_lines,MRC\n");
    fileWriter5.write("cache_lines,MRC\n");
    fileWriter6.write("cache_lines,MRC\n");
    fileWriter7.write("cache_lines,MRC\n");
    fileWriter8.write("cache_lines,MRC\n");


   for(int j = 0; j < countMin; j++)
   {
      //System.out.println(j);
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
      //System.out.println(j+","+relative_error8[j]+"  ,  "+data1.get(j)+"  ,  "+out_data8.get(j));


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

   for(int j = 0; j < length; j++)
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

   fileWriter9.write("drop_rate,abs_err,relative_err\n");
   fileWriter9.write("10,"+ave_abs_error2+","+ave_relative_error2+"\n");
   fileWriter9.write("25,"+ave_abs_error3+","+ave_relative_error3+"\n");
   fileWriter9.write("40,"+ave_abs_error4+","+ave_relative_error4+"\n");
   fileWriter9.write("50,"+ave_abs_error5+","+ave_relative_error5+"\n");
   fileWriter9.write("60,"+ave_abs_error6+","+ave_relative_error6+"\n");
   fileWriter9.write("drop,"+ave_abs_error7+","+ave_relative_error7+"\n");
   fileWriter9.write("90,"+ave_abs_error8+","+ave_relative_error8+"\n");


   fileWriter2.close();
   fileWriter3.close();
   fileWriter4.close();
   fileWriter5.close();
   fileWriter6.close();
   fileWriter7.close();
   fileWriter8.close();
   fileWriter9.close();

  } 


} 