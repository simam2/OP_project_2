
  

# OP project

### v1.2

- Programa naudoja klasę duomenims saugoti:
	-  *string* tipas: studento vardas ir pavardė;
	-  *vector (int)* tipo konteineris: namų darbų tarpiniai rezultatai;
	-  *int* tipas: egzamino rezultatas;
	-  *float* tipas: galutiniai balai skaičiuojant vidurkį arba medianą.
- Paleidus programą pateikiami keli pasirinkimai:
	-  **1 - v0.1** funkcionalumas
	-  **2 - nuo v0.2** funkcionalumas - *1 dalis (generavimas)*
	-  **3 - nuo v0.2** funkcionalumas - *2 dalis (apdorojimas)*
	-  **4 - v1.2** funkcionalumas

---

#### 4 funkcionalumas

- Programa sukuria vieną studentą, prideda jam kelis pažymius, įrašo egzamino pažymį, apskaičiuoja galutinius vidurkį ir medianą, atspausdina šį studentą.
- Padaro šio studento kopiją pasinaudojant kopijavimo konstruktoriumi, atspausdina šį studentą.
- Prideda kelis naujus pažymius naujai nukopijuotam studentui, perskaičiuoja galutinius vidurkį ir medianą ir atspausdina šį studentą.

![](https://raw.githubusercontent.com/simam2/OP_project_2/v1.2/screenshots/1.2.png)

#### 2, 3 funkcionalumai
- Programa leidžia ranka įvesti studentų skaičių kuriam turėtų būti sugeneruotas (arba buvo sugeneruotas) failas (jeigu konstantų faile nėra nurodytas failų sąrašas).
- 2 funkcionalume programa sugeneruoja failą su nurodytu skaičiumi studentų. Faile saugomi duomenys - vardas, pavardė ir galutinis pažymys (skaičiuotas su pažymiu vidurkiu, pažymiai generuojami atsitiktinai). Duomenys faile yra išrikiuoti pagal galutinį pažymį didėjančia tvarka.
- 3 funkcionalume programa nuskaito nurodyto skaičiaus studentų sugeneruotą failą, padalina studentus į du sąrašus (pirmas sąrašas yra sudarytas iš tų studentų, kurių galutinis pažymys yra mažesnis nei 0.5, antrame sąraše - kurių pažymys didesnis arba lygus 0.5) ir išsaugo šiuos atskirų sąrašų duomenis į naujus failus.
- Nuo v1.0 viskas atliekama tik su vector.

Abiems funkcionalumams yra skaičiuojama kiek laiko užtruko jų atskiri veiksmai. Žemiau pateikiami šių skaičiavimų rezultatai (pateikiami vidurkiai sekundėmis iš 5 programos vykdymų su tokiu pačiu kiekiu duomenų naudojant vector tipą - pirmas skaičius naudojant Class ir jos aprašytas funkcijas, antras - Struct):

| Studentų kiekis | Studentų dalinimas į du sąrašus | Bendra trukmė |
| -- | -- | -- |
| 1000 | 0.007 / 0.001 | 0.0476 / 0.043 |
| 10000 | 0.3074 / 0.1572 | 2.1812 / 2.482 |
| 100000 | 8.772 / 1.1104 | 54.0448 / 22.224 |

v1.1 versijoje taip pat atlikti greitaveikos ir optimizacijos testai naudojant skirtingus optimizavimo flag'us. Žemiau pateikiama lentelė su studentų skirstymo trukmėmis ir .exe failo dydžiais (pirmas skaičius - Class, antras - Struct).

| Flag | .exe dydis (MB) | 1000 | 10000 | 100000 |
| -- | -- | -- | -- | -- |
| O1 | 1.37 / 1.38 | 0.0072 / 0.001 | 0.259 / 0.1568 | 8.7348 / 1.0996 |
| O2 | 1.46 / 1.48 | 0.0074 / 0.001 | 0.2876 / 0.1658 | 8.665 / 1.098 |
| O3 | 1.31 / 1.36 | 0.007 / 0.001 | 0.3 / 0.1612 | 8.917 / 1.0998 |

---

#### 1 funkcionalumas
- Programa leidžia ranka įvesti visus duomenis.
- Programa leidžia nuskaityti duomenis iš failo.
- Programa rezultatus parodo ekrana arba atspausdina į failą.
- Paleidus programą, naudotojui pateikiami keli pasirinkimai:
- Programai nereikia iš anksto žinoti kiek studentų (ar jų pažymių) bus įvesta - jeigu nebenorima įvesti daugiau įrašų, kai prašoma įvesti studento vardą (arba pažymį) užtenka nieko neįrašyti ir paspausti ENTER.
- Baigus duomenų įvedimą (ir programai sugeneravus pažymius studentams, jeigu tai buvo pasirinkta) programa suskaičiuoja studentų galutinius balus pasirinktu metodu ir išveda rezultatus į ekraną.

---