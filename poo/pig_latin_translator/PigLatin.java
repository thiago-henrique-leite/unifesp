package JavaProjects.pig_latin_translator;

import java.lang.String;
import java.util.StringTokenizer;
import java.util.Scanner;

public class PigLatin {

	public static String translateEnglishToPigLatin(String phrase) {
		StringTokenizer tokens = new StringTokenizer(phrase);
		String word, first_letter, remaining;
		String ay = "ay", translated_phrase = "";
		
		int amount_tokens = tokens.countTokens();
		int cont=0;
				
		while (tokens.hasMoreTokens()) {
			word = tokens.nextToken();
			
			first_letter = word.substring(0, 1).toLowerCase();
			remaining = word.substring(1).toLowerCase();
			translated_phrase = translated_phrase.concat(remaining).concat(first_letter).concat(ay);
			
			cont++;
			if(amount_tokens != cont) translated_phrase = translated_phrase.concat(" ");
		}
		
		return translated_phrase;
	}
	
	public static void main(String args[]) {
		Scanner ler = new Scanner(System.in);
		String phrase;
		
		System.out.print("\nInsira uma frase: ");
		phrase = ler.nextLine();
		
		String translated_phrase = PigLatin.translateEnglishToPigLatin(phrase);
		System.out.printf("\nFrase em PigLatin: %s\n", translated_phrase);
		
		ler.close();
	}
}

