# ⛵ Pilote Automatique

Pilote automatique pour robot voilier RC, avec deux modes de contrôle :
- **Suivi de cap** (heading hold)
- **Suivi d’allure** (apparent wind angle / AWA)

Le projet est composé de :
- un **firmware Arduino** (`sketch/` + `Librairies/`),
- une **application Python** (`python/main.py`) qui journalise les données reçues via `Arduino_RouterBridge`.

---

## 📁 Structure du dépôt

```text
.
├── app.yaml                # Métadonnées de l'application
├── README.md
├── sketch/
│   ├── sketch.ino          # Point d'entrée firmware
│   └── sketch.yaml         # Profil Arduino CLI (plateforme + libs)
├── Librairies/
│   ├── CONFIG.h            # Constantes globales et paramètres
│   ├── COM.*               # Lecture commandes RC (rudder + mode)
│   ├── IMU.*               # Capteur BNO08x et heading magnétique
│   ├── GPS.*               # GPS (Adafruit_GPS)
│   ├── WINDSENSOR.*        # Angle vent apparent + filtrage EMA
│   ├── RUDDER.*            # Contrôle servo de gouvernail
│   └── DATA.*              # Envoi télémétrie vers la couche Python
└── python/
    └── main.py             # Réception des trames + log CSV
```

---

## ⚙️ Fonctionnement global

Dans la boucle principale (`loop`) :
1. Le firmware met à jour tous les modules capteurs/actionneurs (`update()`),
2. Sérialise une ligne de télémétrie (`save_data()`),
3. Choisit la commande de gouvernail selon le mode :
   - manuel (commande RC),
   - autonome (calcul depuis consigne cap/allure).

La télémétrie est transmise à Python via :
- `DATA::save_data(...)` côté firmware (`Bridge.notify("log_data", ...)`),
- `Bridge.provide("log_data", log_data)` côté Python.

Le logger Python crée des fichiers CSV horodatés dans `python/data/`.

---

## 🧩 Modules firmware

### `COM`
- Lit les signaux PWM de la radio (rudder, mode).
- Expose `is_unmanned()` et `get_com_rudder()`.

### `IMU`
- Initialise le BNO08x sur I2C (`Wire1`).
- Calcule un heading magnétique en degrés `[0..360)`.

### `GPS`
- Configure le GPS en 1 Hz.
- Expose latitude / longitude en degrés décimaux.

### `WINDSENSOR`
- Lit l’angle vent apparent depuis une entrée analogique.
- Optionnellement applique un filtre EMA (`alpha_EMA`).

### `RUDDER`
- Pilote un servo via shield PWM Adafruit.
- Lit la position gouvernail via ADC.

### `DATA`
- Pont vers la couche Python pour persistance des mesures.

---

## 🔧 Configuration

La majorité des paramètres sont centralisés dans `Librairies/CONFIG.h` :
- pins (`PIN_COM_RUDDER`, `PIN_MODE_CONTROL`, `PIN_WINDSENSOR`, ...),
- paramètres servo (min/max pulse, angle max),
- filtre (`EMAfilter`, `alpha_EMA`),
- gain de pilotage (`Kp`),
- flags de compilation :
  - `full_unmanned_mode`
  - `awa_follow_mode`

> Conseil : conserver une seule source de vérité dans `CONFIG.h` pour tout réglage terrain.

---

## ▶️ Lancer la partie Python (logging)

Prérequis : environnement Arduino App / `arduino.app_utils` disponible.

Depuis la racine du dépôt :

```bash
python -m py_compile python/main.py
python python/main.py
```

Au démarrage, l’app affiche le chemin du CSV actif.

---

## 🏗️ Build firmware

Le projet contient un profil `sketch/sketch.yaml` listant les bibliothèques nécessaires.

Exemple générique (à adapter selon votre carte/FQBN) :

```bash
arduino-cli compile --build-path build --fqbn <votre_fqbn> sketch
arduino-cli upload -p <votre_port> --fqbn <votre_fqbn> sketch
```

Si vous utilisez l’écosystème Arduino App avec RouterBridge, gardez la cohérence entre :
- le firmware (`Bridge.notify`),
- le service Python (`Bridge.provide`).

---

## 📊 Format des logs CSV

Colonnes produites :
- `timestamp_ms`
- `latitude`
- `longitude`
- `heading`
- `rudder_angle`
- `awa`
- `filtered_awa`
- `unmanned_status`

---

## 🚀 Prochaines améliorations recommandées

- Ajouter des **tests de compilation firmware** en CI (Arduino CLI).
- Documenter précisément les **modes RC/autonome** (seuil PWM et convention).
- Ajouter une section de **calibration capteurs** (IMU, vent, gouvernail).
- Ajouter un schéma de câblage (pins et alimentation).

---

## 📝 Licence

Aucune licence explicite n’est définie actuellement dans le dépôt.
Ajouter un fichier `LICENSE` est recommandé pour clarifier les conditions d’utilisation.
