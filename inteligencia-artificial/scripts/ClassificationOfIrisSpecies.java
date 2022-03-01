package ia.aula09.pratico;

import java.util.*;
import java.io.File;
import java.io.IOException;
import jxl.Cell;
import jxl.Sheet;
import jxl.Workbook;
import jxl.read.biff.BiffException;

public class ClassificationOfIrisSpecies {
	
	List<Double> sepalLengthCm, sepalWidthCm, petalLengthCm, petalWidthCm;
	List<Double> slcmTest, swcmTest, plcmTest, pwcmTest;
	
	List<Integer> idsTest;
	
	List<Double> euclideanDists;
	
	List<String> irisSpecies, irisSpeciesTest;
	
	Map<Double, String> distanceSpecie;
	
	Map<String, Integer> specieOccurrences;
		
	private int k, testCases, trainedCases;
	
	public ClassificationOfIrisSpecies(String spreadsheetPath, String spreadsheetTestPath, int k) throws BiffException, IOException {
		setK(k);
		setHashMaps();
		setArrayLists();
		readSpreadsheet(spreadsheetPath);
		readTestSpreadsheet(spreadsheetTestPath);
	}
	
	public void perform() {
        readInfoOfUser();
	}
	
	public void setArrayLists() {
		sepalLengthCm  = new ArrayList<>();
		sepalWidthCm   = new ArrayList<>();
		petalLengthCm  = new ArrayList<>();
		petalWidthCm   = new ArrayList<>();
		
		slcmTest = new ArrayList<>();
		swcmTest = new ArrayList<>();
		plcmTest = new ArrayList<>();
		pwcmTest = new ArrayList<>();
		idsTest  = new ArrayList<>();
		
		irisSpecies     = new ArrayList<>();
		irisSpeciesTest = new ArrayList<>();
		euclideanDists  = new ArrayList<>();
	}
	
	public void setHashMaps() {
		distanceSpecie    = new HashMap<>();
		specieOccurrences = new HashMap<>();
	}
	
    public void setK(int k) {
		this.k = k;
	}
	
	public void readInfoOfUser() {
		@SuppressWarnings("resource")
		Scanner read = new Scanner(System.in);
		
		System.out.print("Comprimento da sépala em cm: ");
		double slcm = read.nextDouble();
		
		System.out.print("Largura da sépala em cm:     ");
		double swcm = read.nextDouble();
		
		System.out.print("Comprimento da pétala em cm: ");
		double plcm = read.nextDouble();
		
		System.out.print("Largura da pétala em cm:     ");
		double pwcm = read.nextDouble();
		
		System.out.println("\nEspécie: " + classifyIrisByKnnAlgorithm(slcm, swcm, plcm, pwcm));
	}
	
	public void knnAlgorithm() {
		List<String> errors = new ArrayList<>();
		
		String response;
		
		int hits=0, wrong=0;
		
		System.out.println("#### SOLUÇÃO PELO ALGORITMO KNN ####\n");

		for(int i=0; i<testCases; i++) {
			response = classifyIrisByKnnAlgorithm(slcmTest.get(i), swcmTest.get(i), plcmTest.get(i), pwcmTest.get(i));
		
			if(response.equals(irisSpeciesTest.get(i))) {
				hits++;
			} else {
				wrong++;
				errors.add("Id: " + idsTest.get(i) + " - Saída esperada: " + irisSpeciesTest.get(i) + " - Saída obtida: " + response);
			}
			
			clearLocalData();
		}
		
		double accuracy = ((double) hits*100)/testCases;
		
		printResults(hits, wrong, accuracy);
		printErrors(errors);
	}
	
	void printResults(int hits, int wrong, double accuracy) {
		System.out.printf("Aprendizado Supervisionado - DataSet IRIS\n\n");
		System.out.printf("Espécies fornecidas para aprendizagem: %d espécies.\n\n", trainedCases);
		System.out.printf("Tamanho da amostra: %d espécies teste.\n", testCases);
		System.out.println("\tAcertos:  " + hits);
		System.out.println("\tErros:    " + wrong);
		System.out.printf("\tAcurácia: %.2f%%\n\n", accuracy);
	}
	
	public void printErrors(List<String> errors) {
		Iterator<String> it = errors.iterator();
		
		System.out.println("Erros encontrados:");
		while(it.hasNext())
			System.out.println("\t" + it.next());
	}
	
	public void clearLocalData() {
		euclideanDists.clear();
		distanceSpecie.clear();
		specieOccurrences.clear();
	}
	
	public String getSpecie(int index) {
		return distanceSpecie.get(euclideanDists.get(index));
	}
	
	public String getSpecieWithBiggerOccurrence() {
				
		for(int i=0; i<k; i++)
			specieOccurrences.put(getSpecie(i), 0);
		
		for(int j=0; j<k; j++) 
			specieOccurrences.put(getSpecie(j), specieOccurrences.get(getSpecie(j))+1);
				
		int specieBiggerOcurrence = specieOccurrences.get(getSpecie(0));
		String final_specie = getSpecie(0); 
		
		Iterator<String> it = specieOccurrences.keySet().iterator();
		
		while(it.hasNext()) {
			String aux = it.next();
			int specieOccurrence = specieOccurrences.get(aux);
			
			if(specieOccurrence > specieBiggerOcurrence) {
				specieBiggerOcurrence = specieOccurrence;
				final_specie = aux; 
			}
		}
		
		return final_specie;
	}
	
	public String classifyIrisByKnnAlgorithm(double slcm, double swcm, double plcm, double pwcm) {
		String irisSpecie;
		Double distance;
		
		for(int i=0; i<trainedCases; i++) {
			distance = euclideanDistance(i, slcm, swcm, plcm, pwcm);
			euclideanDists.add(distance);
			distanceSpecie.put(distance, irisSpecies.get(i));
		}
		
		euclideanDists.sort(null);
		
		irisSpecie = getSpecieWithBiggerOccurrence();
		
		return irisSpecie;
	}
	
	public Double euclideanDistance(int i, Double slcm, Double swcm, Double plcm, Double pwcm) {
		Double sepalLengthDiff = Math.pow(sepalLengthCm.get(i)-slcm, 2);
		Double sepalWidthDiff  = Math.pow(sepalWidthCm.get(i)-swcm, 2);
		Double petalLengthDiff = Math.pow(petalLengthCm.get(i)-plcm, 2);
		Double petalWidthDiff  = Math.pow(petalWidthCm.get(i)-pwcm, 2);
		
		return sepalLengthDiff + sepalWidthDiff + petalLengthDiff + petalWidthDiff;
	}
	
	public void readSpreadsheet(String path) throws BiffException, IOException {
		Workbook workbook = Workbook.getWorkbook(new File(path));
		Sheet sheet = workbook.getSheet(0);
		
		trainedCases = sheet.getRows() - 1;
		
		for(int i = 1; i <= trainedCases; i++) {
			Cell b = sheet.getCell(1, i);
			Cell c = sheet.getCell(2, i);
			Cell d = sheet.getCell(3, i);
			Cell e = sheet.getCell(4, i);
			Cell f = sheet.getCell(5, i);
			
			sepalLengthCm.add(Double.parseDouble(b.getContents()));
			sepalWidthCm.add(Double.parseDouble(c.getContents()));
			petalLengthCm.add(Double.parseDouble(d.getContents()));
			petalWidthCm.add(Double.parseDouble(e.getContents()));
			irisSpecies.add(f.getContents());			
		}
		
		workbook.close();
	}
	
	public void readTestSpreadsheet(String spreadsheetTestPath) throws BiffException, IOException {
		Workbook workbook = Workbook.getWorkbook(new File(spreadsheetTestPath));
		Sheet sheet = workbook.getSheet(0);
		testCases = sheet.getRows() - 1;
			
		for(int i = 1; i <= testCases; i++) {
			idsTest.add(Integer.parseInt(sheet.getCell(0, i).getContents()));
			slcmTest.add(Double.parseDouble(sheet.getCell(1, i).getContents()));
			swcmTest.add(Double.parseDouble(sheet.getCell(2, i).getContents()));
			plcmTest.add(Double.parseDouble(sheet.getCell(3, i).getContents()));
			pwcmTest.add(Double.parseDouble(sheet.getCell(4, i).getContents()));
			
			irisSpeciesTest.add(sheet.getCell(5, i).getContents());
		}
		
		workbook.close();
	}
	
	public static void main(String args[]) throws BiffException, IOException {
		String iris_path = "/home/thiagoleite/Documentos/unifesp/ia/Iris.xls";
		String iris_test_path = "/home/thiagoleite/Documentos/unifesp/ia/Iris-Testes.xls";
		
		ClassificationOfIrisSpecies datasetIris = new ClassificationOfIrisSpecies(iris_path, iris_test_path, 11);
		
		datasetIris.knnAlgorithm();
	}
}
