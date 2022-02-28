package JavaProjects.concorrencia;

import java.util.Scanner;

public class CountPrimeNumbers extends Thread {
	private int first, last, threads_number, counter=0;
	
	public CountPrimeNumbers(int first, int last, int threads_number) {
		this.first = first;
		this.last = last;
		this.threads_number = threads_number;
		divided_numbers();
	}
	
	public void divided_numbers() {
		int numbersPerThread = (int) Math.round((float) (last - first + 1) / threads_number);
		
		divided_threads(numbersPerThread);
	}
	
	public void divided_threads(int numberPerThread) {
		int inicio = first, fim = first + numberPerThread - 1;
		
		MyThreadRunnable t1 = null, t2 = null, t3 = null, t4 = null, t5 = null;
		
		for(int i=1; i<=threads_number; i++) {
			
			switch(i) {
			case 1:
				t1 = new MyThreadRunnable(inicio, fim);
				break;
			case 2: 
				t2 = new MyThreadRunnable(inicio, fim);
				break;
			case 3:
				t3 = new MyThreadRunnable(inicio, fim);
				break;
			case 4: 
				t4 = new MyThreadRunnable(inicio, fim);
				break;
			case 5:
				t5 = new MyThreadRunnable(inicio, fim);
				break;
			}
			
			inicio = fim + 1;
			fim = inicio + numberPerThread - 1;
			
			if(i+1==threads_number)
				fim = last;
		}
		
		try {
			Thread.sleep(1000);
			if(t1!=null) counter += t1.getCounter();
			if(t2!=null) counter += t2.getCounter();
			if(t3!=null) counter += t3.getCounter();
			if(t4!=null) counter += t4.getCounter();
			if(t5!=null) counter += t5.getCounter();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		System.out.println("\nQuantidade de números primos no intervalo [" + first + "," + last + "] = " + counter);
	}
	
	public static void main(String[] args) {
		Scanner read = new Scanner(System.in);
		int first, last, threads_number;
		
		System.out.print("Entre com o número inicial: ");
		first = read.nextInt();
		
		System.out.print("Entre com o número final: ");
		last = read.nextInt();
		
		System.out.print("Entre com o número de threads (1 a 5): ");
		threads_number = read.nextInt();
		
		new CountPrimeNumbers(first, last, threads_number);
		
		read.close();
	}

}