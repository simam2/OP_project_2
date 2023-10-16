
# OP project
### v0.2

 - Programa naudoja struktūrą duomenims saugoti:
	 - *string* tipas: studento vardas ir pavardė;
	 - *vector (int)* tipo konteineris: namų darbų tarpiniai rezultatai; 
	 - *int* tipas: egzamino rezultatas;
	 - *float* tipas: galutiniai balai skaičiuojant vidurkį arba medianą.
 - Paleidus programą pateikiami keli pasirinkimai:
			 - **1 - v0.1** funkcionalumas
			 - **2 - v0.2** funkcionalumas - *1 dalis*
			 - **3 - v0.2** funkcionalumas - *2 dalis*

---

#### 2, 3 funkcionalumai

- Programa leidžia ranka įvesti studentų skaičių kuriam turėtų būti sugeneruotas (arba buvo sugeneruotas) failas.
- 2 funkcionalume programa sugeneruoja failą su nurodytu skaičiumi studentų. Faile saugomi duomenys - vardas, pavardė ir galutinis pažymys (skaičiuotas su pažymiu vidurkiu, pažymiai generuojami atsitiktinai). Duomenys faile yra išrikiuoti pagal galutinį pažymį didėjančia tvarka.
- 3 funkcionalume programa nuskaito nurodyto skaičiaus studentų sugeneruotą failą, padalina studentus į du sąrašus (pirmas sąrašas yra sudarytas iš tų studentų, kurių galutinis pažymys yra mažesnis nei 0.5, antrame sąraše - kurių pažymys didesnis arba lygus 0.5) ir išsaugo šiuos atskirų sąrašų duomenis į naujus failus.

Abiems funkcionalumams yra skaičiuojama kiek laiko užtruko jų atskiri veiksmai. Žemiau pateikiami šių skaičiavimų rezultatai (pateikiami vidurkiai sekundėmis iš 5 programos vykdymų su tokiu pačiu kiekiu duomenų):

| Studentų kiekis | Pradinio failo generavimas | Duomenų nuskaitymas iš failo | Studentų dalinimas į du sąrašus | Studentų įrašymas į du naujus failus |
| -- | -- | -- | -- | -- |
| 1000 | 0.0166 | 0.0046 | 0 | 0.0032 |
| 10000 | 0.122 | 0.0304 | 0.002 | 0.102 |
| 100000 | 1.167 | 0.267 | 0.0202 | 0.196 |
| 1000000 |1 1.516 | 2.637 | 0.227 | 1.97 |
| 10000000 | 122.518 | 26.609 | 2.145 | 23.823 |


---

#### 1 funkcionalumas

- Programa leidžia ranka įvesti visus duomenis.
	- Programa leidžia nuskaityti duomenis iš failo.
	- Programa rezultatus parodo ekrana arba atspausdina į failą.
	- Paleidus programą, naudotojui pateikiami keli pasirinkimai:
 - Programai nereikia iš anksto žinoti kiek studentų (ar jų pažymių) bus įvesta - jeigu nebenorima įvesti daugiau įrašų, kai prašoma įvesti studento vardą (arba pažymį) užtenka nieko neįrašyti ir paspausti ENTER.
 - Baigus duomenų įvedimą (ir programai sugeneravus pažymius studentams, jeigu tai buvo pasirinkta) programa suskaičiuoja studentų galutinius balus pasirinktu metodu ir išveda rezultatus į ekraną.

---