
# OP project
### v0.3

 - Programa naudoja struktūrą duomenims saugoti:
	 - *string* tipas: studento vardas ir pavardė;
	 - *vector (int)* tipo konteineris: namų darbų tarpiniai rezultatai; 
	 - *int* tipas: egzamino rezultatas;
	 - *float* tipas: galutiniai balai skaičiuojant vidurkį arba medianą.
 - Paleidus programą pateikiami keli pasirinkimai:
	 - **1 - v0.1** funkcionalumas
	 - **2 - v0.2 + v0.3** funkcionalumas - *1 dalis*
	 - **3 - v0.2 + v0.3** funkcionalumas - *2 dalis*

---

#### 2, 3 funkcionalumai

- Programa leidžia ranka įvesti studentų skaičių kuriam turėtų būti sugeneruotas (arba buvo sugeneruotas) failas (jeigu konstantų faile nėra nurodytas failų sąrašas).
- 2 funkcionalume programa sugeneruoja failą su nurodytu skaičiumi studentų. Faile saugomi duomenys - vardas, pavardė ir galutinis pažymys (skaičiuotas su pažymiu vidurkiu, pažymiai generuojami atsitiktinai). Duomenys faile yra išrikiuoti pagal galutinį pažymį didėjančia tvarka.
- 3 funkcionalume programa nuskaito nurodyto skaičiaus studentų sugeneruotą failą, padalina studentus į du sąrašus (pirmas sąrašas yra sudarytas iš tų studentų, kurių galutinis pažymys yra mažesnis nei 0.5, antrame sąraše - kurių pažymys didesnis arba lygus 0.5) ir išsaugo šiuos atskirų sąrašų duomenis į naujus failus.
- Visi žingsniai yra atliekami atskirai su vector ir su list tipais greitaveikai palyginti.

Abiems funkcionalumams yra skaičiuojama kiek laiko užtruko jų atskiri veiksmai. Žemiau pateikiami šių skaičiavimų rezultatai (pateikiami vidurkiai sekundėmis iš 5 programos vykdymų su tokiu pačiu kiekiu duomenų, pirmas skaičius - vector, antras - list):

| Studentų kiekis | Pradinio failo generavimas | Duomenų nuskaitymas iš failo | Studentų dalinimas į du sąrašus | Studentų (<5) įrašymas į naują failą | Studentų (>5) įrašymas į naują failą | Bendra trukmė |
| -- | -- | -- | -- | -- | -- | -- |
| 1000 | 0.1704 / 0.4244 | 0.424 / 0.6742 | 0.002 / 0.0482 | 0.0346 / 0.0164 | 0.033 / 0.0246 | 0.4906 / 0.8034 | 
| 10000 | 4.7072 / 8.1412 | 1.3302 / 16.8854 | 0.0096 / 1.099 | 0.1238 / 0.0962 | 0.1614 / 0.1424 | 1.6148 / 19.8172 |
| 100000 | 31.5758 / 20.7914 | 2.8704 / 40.8884 | 0.0944 / 0.2224 | 0.8718 / 0.9358 | 1.1632 / 1.5234 | 5.0138 / 63.4508 |
| 1000000 | x | x | x | x | x | x |
| 10000000 | x | x | x | x | x | x |


| Studentų kiekis | 2 | 3 |
| -- | -- | -- |
| 1000 | ![](https://github.com/simam2/OP_project/blob/v0.3/screenshots/2_1000.png?raw=true) | ![](https://github.com/simam2/OP_project/blob/v0.3/screenshots/3_1000_1.png?raw=true) ![](https://github.com/simam2/OP_project/blob/v0.3/screenshots/3_1000_2.png?raw=true) | 
| 10000 | ![](https://github.com/simam2/OP_project/blob/v0.3/screenshots/2_10000.png?raw=true) | ![](https://github.com/simam2/OP_project/blob/v0.3/screenshots/3_10000_1.png?raw=true) ![](https://github.com/simam2/OP_project/blob/v0.3/screenshots/3_10000_2.png?raw=true) | 
| 100000 | ![](https://github.com/simam2/OP_project/blob/v0.3/screenshots/2_100000.png?raw=true) | ![](https://github.com/simam2/OP_project/blob/v0.3/screenshots/3_100000_1.png?raw=true) ![](https://github.com/simam2/OP_project/blob/v0.3/screenshots/3_100000_2.png?raw=true) | 
| 1000000 | x | x |
| 10000000 | x | x |

Greitaveikos testai vykdyti su toliau nurodytų parametrų kompiuteriu: CPU - Intel i5-10210U, 8GB RAM, SSD, Windows OS.


---

#### 1 funkcionalumas

- Programa leidžia ranka įvesti visus duomenis.
	- Programa leidžia nuskaityti duomenis iš failo.
	- Programa rezultatus parodo ekrana arba atspausdina į failą.
	- Paleidus programą, naudotojui pateikiami keli pasirinkimai:
 - Programai nereikia iš anksto žinoti kiek studentų (ar jų pažymių) bus įvesta - jeigu nebenorima įvesti daugiau įrašų, kai prašoma įvesti studento vardą (arba pažymį) užtenka nieko neįrašyti ir paspausti ENTER.
 - Baigus duomenų įvedimą (ir programai sugeneravus pažymius studentams, jeigu tai buvo pasirinkta) programa suskaičiuoja studentų galutinius balus pasirinktu metodu ir išveda rezultatus į ekraną.

---