
# OP project
### v0.3

 - Programa naudoja struktūrą duomenims saugoti:
	 - *string* tipas: studento vardas ir pavardė;
	 - *vector (int)* tipo konteineris: namų darbų tarpiniai rezultatai; 
	 - *int* tipas: egzamino rezultatas;
	 - *float* tipas: galutiniai balai skaičiuojant vidurkį arba medianą.
 - Paleidus programą pateikiami keli pasirinkimai:
	 - **1 - v0.1** funkcionalumas
	 - **2 - v0.2 + v0.3 + v1.0** funkcionalumas - *1 dalis*
	 - **3 - v0.2 + v0.3 + v1.0** funkcionalumas - *2 dalis*

---

#### 2, 3 funkcionalumai

- Programa leidžia ranka įvesti studentų skaičių kuriam turėtų būti sugeneruotas (arba buvo sugeneruotas) failas (jeigu konstantų faile nėra nurodytas failų sąrašas).
- 2 funkcionalume programa sugeneruoja failą su nurodytu skaičiumi studentų. Faile saugomi duomenys - vardas, pavardė ir galutinis pažymys (skaičiuotas su pažymiu vidurkiu, pažymiai generuojami atsitiktinai). Duomenys faile yra išrikiuoti pagal galutinį pažymį didėjančia tvarka.
- 3 funkcionalume programa nuskaito nurodyto skaičiaus studentų sugeneruotą failą, padalina studentus į du sąrašus (pirmas sąrašas yra sudarytas iš tų studentų, kurių galutinis pažymys yra mažesnis nei 0.5, antrame sąraše - kurių pažymys didesnis arba lygus 0.5) ir išsaugo šiuos atskirų sąrašų duomenis į naujus failus.
- v1.0 visi žingsniai visose strategijose yra atliekami su vector.

Abiems funkcionalumams yra skaičiuojama kiek laiko užtruko jų atskiri veiksmai. Žemiau pateikiami šių skaičiavimų rezultatai (pateikiami vidurkiai sekundėmis iš 5 programos vykdymų su tokiu pačiu kiekiu duomenų, pirmas skaičius - 1 strategijos, antras - antros ir trečias trečios):

| Studentų kiekis | Studentų dalinimas į du sąrašus | Bendra trukmė |
| -- | -- | -- |
| 1000 | 0.003 / 0.014 / 0.002 | 0.103 / 0.088 / 0.102 | 
| 10000 | 0.262 / 1.268 / 0.244 | 4.817 / 5.743 / 5.724 |
| 100000 | 1.703 / 1014.714 / 1.75 | 35.231 / 1112.117 / 37.7086 |

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