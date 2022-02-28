package JavaProjects.concorrencia;

public class MyThreadRunnable implements Runnable {

	private int first, last, counter=0;

	public MyThreadRunnable(int first, int last) {
		this.first = first;
		this.last = last;
		new Thread(this).start();
	}

	public void run() {
		boolean isPrime;
		for(int i=first; i<=last; i++) {
			isPrime=true;
			
			for(int j=2; j<=Math.sqrt(i); j++) 
				if(i%j==0) 
					isPrime=false;
			
			if(isPrime && i>1)
				counter++;
		}
	}

	public int getCounter() {
		return counter;
	}

}