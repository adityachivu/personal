import java.util.*;
import java.lang.*;
import java.io.*;
import java.util.Iterator;

public class Main {
	
	public static void main(String[] args) throws IOException
	{
		ArrayList<int[][]> class0 = new ArrayList<int[][]>();
		ArrayList<int[][]> class1 = new ArrayList<int[][]>();
		ArrayList<int[][]> class2 = new ArrayList<int[][]>();
		ArrayList<int[][]> class3 = new ArrayList<int[][]>();
		ArrayList<int[][]> class4 = new ArrayList<int[][]>();
		ArrayList<int[][]> class5 = new ArrayList<int[][]>();
		ArrayList<int[][]> class6 = new ArrayList<int[][]>();
		ArrayList<int[][]> class7 = new ArrayList<int[][]>();
		ArrayList<int[][]> class8 = new ArrayList<int[][]>();
		ArrayList<int[][]> class9 = new ArrayList<int[][]>();
		
		float[] priors = new float[10];
		
		String fileName = "trainingimages";
		String fileLabel = "traininglabels";
		String testName = "testimages";
		String testLabel = "testlabels";
		
		BufferedReader br = null;
		BufferedReader br1 = null;
		
		int q=1;		//since k=1 gave maximum accuracy
		//System.out.print("Enter the value of k: ");
		//Scanner sc = new Scanner(System.in);
		//q=sc.nextInt();
		

		try {

			String sCurrentLine;
			String sCurrentLine1;
			
			int count=28;
			int label;
			
			

			br = new BufferedReader(new FileReader(fileName));
			br1 = new BufferedReader(new FileReader(fileLabel));
			int i,j;
			char b;

			while ((sCurrentLine1 = br1.readLine()) != null) 
			{
				count=28;
				label=Integer.parseInt(sCurrentLine1);
				int[][] a = new int[28][28];
				i=0;
				j=0;
				while(count>0)
				{
					sCurrentLine = br.readLine();
					for(j=0;j<28;j++)
					{
						b = sCurrentLine.charAt(j);
						if(b == ' ')
							a[i][j]= 0;
						else
							a[i][j]= 1;
					}
					i++;
					//System.out.println(count);
					count--;
					/*for(int m=0;m<28;m++)
						{
						for(int n=0;n<28;n++)
							System.out.print(a[m][n]);
						System.out.println();
						}
					System.out.println();
					break;*/
						
					
				}
				
				switch(label)
				{
				case 0: class0.add(a);
						break;
				case 1: class1.add(a);
						break;
				case 2: class2.add(a);
						break;
				case 3: class3.add(a);
						break;
				case 4: class4.add(a);
						break;
				case 5: class5.add(a);
						break;
				case 6: class6.add(a);
						break;
				case 7: class7.add(a);
						break;
				case 8: class8.add(a);
						break;
				case 9: class9.add(a);
						break;
				}
			
				
			}

			}
		catch (IOException e) 
			{
			e.printStackTrace();
			} 
		finally 
			{
			try 
				{
				if (br != null)
					br.close();
				if (br1 != null)
					br1.close();
				} 
			catch (IOException ex) 
				{
				ex.printStackTrace();
				}
			}
		
		float total = 5000;
		//System.out.println(total);
		
		/*System.out.println(class0.size());
		System.out.println(class1.size());
		System.out.println(class2.size());
		System.out.println(class3.size());
		System.out.println(class4.size());
		System.out.println(class5.size());
		System.out.println(class6.size());
		System.out.println(class7.size());
		System.out.println(class8.size());
		System.out.println(class9.size());*/
		
		/*int [][] sample = new int[28][28];
		
		for(int x=0;x<500;x++)
			{
			sample=class0.get(x);
			
			for(int m=0;m<28;m++)
			{
					for(int n=0;n<28;n++)
							System.out.print(sample[m][n]);
					System.out.println();
			}
			System.out.println();
			}*/
		
		
		
		priors[0]=class0.size()/total;
		priors[1]=class1.size()/total;
		priors[2]=class2.size()/total;
		priors[3]=class3.size()/total;
		priors[4]=class4.size()/total;
		priors[5]=class5.size()/total;
		priors[6]=class6.size()/total;
		priors[7]=class7.size()/total;
		priors[8]=class8.size()/total;
		priors[9]=class9.size()/total;
		
		//for(int i=0;i<10;i++)
			//System.out.println(priors[i]);
		
		float[][][] count_0 = new float[10][28][28];
		
		count_0[0] = array_traversal(class0, class0.size(),q);	
		count_0[1] = array_traversal(class1, class1.size(),q);
		count_0[2] = array_traversal(class2, class2.size(),q);
		count_0[3] = array_traversal(class3, class3.size(),q);
		count_0[4] = array_traversal(class4, class4.size(),q);
		count_0[5] = array_traversal(class5, class5.size(),q);
		count_0[6] = array_traversal(class6, class6.size(),q);
		count_0[7] = array_traversal(class7, class7.size(),q);
		count_0[8] = array_traversal(class8, class8.size(),q);
		count_0[9] = array_traversal(class9, class9.size(),q);
	
		BufferedReader br2 = null;
		BufferedReader br3 = null;
		float final_true=0;
		int[] result = new int[2000];
		

		try {

			String sCurrentLine2;
			String sCurrentLine3;
			
			int count=28;
			int label1;
							

			br2 = new BufferedReader(new FileReader(testName));
			br3 = new BufferedReader(new FileReader(testLabel));
			int i,j;
			char c;
			int k=0;
			

			while ((sCurrentLine3 = br3.readLine()) != null) 
			{
				count=28;
				label1=Integer.parseInt(sCurrentLine3);
				//System.out.println(label1);
				int[][] array = new int[28][28];
				i=0;
				j=0;
				while(count>0)
				{
					sCurrentLine2 = br2.readLine();
					for(j=0;j<28;j++)
					{
						c = sCurrentLine2.charAt(j);
						if(c == ' ')
							array[i][j]= 0;
						else
							array[i][j]= 1;
					}
					i++;
					//System.out.println(count);
					count--;
					
				}
				
				result[k]=classifier(array,priors,count_0);
				
				if(result[k] == label1)
					final_true++;
				
				k++;
				//for(int s=0;s<28;s++)
					//for(int r=0;r<28;r++)
					//	array[s][r]=0;
				
			}

			}
		catch (IOException e) 
			{
			e.printStackTrace();
			} 
		finally 
			{
			try 
				{
				if (br2 != null)
					br2.close();
				if (br3 != null)
					br3.close();
				} 
			catch (IOException ex) 
				{
				ex.printStackTrace();
				}
			}
		
		//for(int i=0;i<1000;i++)
			//System.out.println(result[i]);
		
		System.out.println("Final accuracy is: "+(final_true/1000)*100+"%");
		
		
		try {

	        BufferedWriter writer = new BufferedWriter(new FileWriter("testlabels_1.txt"));
	        for ( int i = 0; i < 1000; i++)
	        {      
	        	writer.write((i+1) + " ");
	        	writer.write(result[i] + " \n");
	        }
	        writer.close();
	    } catch(IOException ex) {
	        ex.printStackTrace();
	    }
		
		
		}
	
		public static float[][] array_traversal(ArrayList<int[][]> temp, int size, int q)
		{
			Iterator iterator = temp.iterator();
			
			float[][] count0 = new float[28][28];
			
			
	        while (iterator.hasNext()) 
	        {
	        	int[][] t = new int[28][28];
	        	t=(int[][]) iterator.next();
	        	
	        	for(int i=0; i<28; i++)
	        	{
	        		for(int j=0; j<28; j++)
	        		{
	        			if(t[i][j]==0)
	        				count0[i][j]=count0[i][j]+1;
	        			
	        		}
	        	}
	        	
	        	
	        }
        	
	        for(int i=0; i<28; i++)
        	{
        		for(int j=0; j<28; j++)
        		{
        			count0[i][j]= (count0[i][j]+q)/(size+2*q);
        			
        		}
        	
        	}
	        
	        
	        return count0;
		}
		
		public static int classifier(int[][] t, float[] priors, float[][][] count_0 )
		{
			int max=0;
			
			float[] posterior = new float[10];
			for(int k=0;k<10;k++)
			{
				posterior[k]=0;
			}
			
			for(int k=0;k<10;k++)
			{
				for(int i=0; i<28; i++)
				{
					for(int j=0; j<28; j++)
					{
						if(t[i][j]== 0)
							posterior[k] = (float) (posterior[k]+ Math.log(count_0[k][i][j]));
						else
							posterior[k] = (float) (posterior[k]+ Math.log(1-count_0[k][i][j]));
						
					}
        	
				}
				posterior[k]=(float) (posterior[k]+(priors[k]));
			}
			
			for(int k=1;k<10;k++)
			{
				if(posterior[k]>posterior[max])
					max=k;
			}
			
			return max;
			
		}
}
