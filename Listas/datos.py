import random
from datetime import datetime

# Configuracion inicial
random.seed(42)  # Para reproducibilidad
current_year = 2025

# Datos de ejemplo (listas expandidas para 35 autores)
nombres_hombres = ["Juan", "Carlos", "Luis", "Pedro", "Miguel", "Jorge", "Andres", "Ricardo", "Fernando", "Diego", 
                  "Gabriel", "Sergio", "Rafael", "Javier", "Martin", "Daniel", "Emilio", "Alberto", "Roberto", "Francisco",
                  "Hector", "Eduardo", "Manuel", "Jose", "Antonio", "Alvaro", "Gustavo", "Raul", "Victor", "Pablo",
                  "Ignacio", "Joaquin", "Federico", "Salvador", "Guillermo", "Enrique", "Armando", "Felipe", "Rodrigo", "Arturo"]

nombres_mujeres = ["Maria", "Ana", "Laura", "Sofia", "Isabel", "Carmen", "Elena", "Lucia", "Patricia", "Adriana", 
                  "Claudia", "Marta", "Teresa", "Rosa", "Silvia", "Paula", "Julia", "Raquel", "Diana", "Valeria",
                  "Beatriz", "Carolina", "Natalia", "Veronica", "Lorena", "Alejandra", "Marina", "Susana", "Ines", "Olga",
                  "Liliana", "Esther", "Rocio", "Victoria", "Jimena", "Gabriela", "Alicia", "Ruth", "Irene", "Monica"]

apellidos = ["Garcia", "Rodriguez", "Gonzalez", "Fernandez", "Lopez", "Martinez", "Sanchez", "Perez", "Gomez", "Martin", 
            "Jimenez", "Ruiz", "Hernandez", "Diaz", "Moreno", "Alvarez", "Romero", "Alonso", "Gutierrez", "Navarro",
            "Torres", "Dominguez", "Vazquez", "Ramos", "Gil", "Ramirez", "Serrano", "Blanco", "Suarez", "Castro",
            "Ortega", "Rubio", "Molina", "Delgado", "Ortiz", "Medina", "Santos", "Cruz", "Morales", "Iglesias"]

ciudades = ["Madrid", "Barcelona", "Valencia", "Sevilla", "Zaragoza", "Buenos Aires", "Cordoba", "Rosario", "Ciudad de Mexico", 
           "Guadalajara", "Monterrey", "Bogota", "Medellin", "Lima", "Santiago", "Caracas", "São Paulo", "Rio de Janeiro", "Paris", "Roma",
           "Berlin", "Lisboa", "amsterdam", "Viena", "Bruselas", "Estocolmo", "Oslo", "Helsinki", "Atenas", "El Cairo",
           "Nueva York", "Londres", "Tokio", "Pekin", "Sidney", "Toronto", "Moscu", "Estambul", "Dubai", "Singapur"]

paises = ["España", "Argentina", "Mexico", "Colombia", "Peru", "Chile", "Venezuela", "Brasil", "Francia", "Italia",
         "Alemania", "Portugal", "Holanda", "Austria", "Belgica", "Suecia", "Noruega", "Finlandia", "Grecia", "Egipto",
         "EE.UU.", "Reino Unido", "Japon", "China", "Australia", "Canada", "Rusia", "Turquia", "Emiratos arabes", "Singapur"]

formaciones = ["literatura", "artes", "ciencias sociales", "ingenierias", "areas de la salud", "jurisprudencia", "otros"]
tipos_poesia = ["decima", "soneto", "himno", "haiku", "romance", "octava real", "lira", "verso libre"]

# Generar 5 editoriales unicas
editoriales_data = []
editorial_nombres = set()
for i in range(1, 6):
    while True:
        nombre = random.choice(["Ediciones", "Editorial", "Libros", "Publicaciones"]) + " " + random.choice([
            "del Sur", "Norte", "Este", "Oeste", "Universal", "Continental", "Global", "Internacional", "Nacional", "Regional"
        ]) + " " + random.choice([
            "Literaria", "Poetica", "Cultural", "Artistica", "Creativa", "Imaginativa", "Expresiva"
        ])
        if nombre not in editorial_nombres:
            editorial_nombres.add(nombre)
            break
    
    ciudad = random.choice(ciudades)
    pais = random.choice(paises)
    editoriales_data.append({
        "id": i,
        "nombre": nombre,
        "ciudad": ciudad,
        "pais": pais
    })

# Generar 35 autores unicos (17 hombres y 18 mujeres)
autores = []
nombres_apellidos = set()
for i in range(1, 36):
    sexo = "M" if i <= 17 else "F"
    nombres = nombres_hombres if sexo == "M" else nombres_mujeres
    
    while True:
        nombre = random.choice(nombres)
        apellido = random.choice(apellidos)
        nombre_completo = f"{nombre} {apellido}"
        
        if nombre_completo not in nombres_apellidos:
            nombres_apellidos.add(nombre_completo)
            break
    
    # Ajuste clave: asegurar que primera obra sea antes de 2025
    año_nac = random.randint(1940, 1975)  # Nacidos como maximo en 1975
    mes_nac = random.randint(1, 12)
    dia_nac = random.randint(1, 28)
    fecha_nac = f"{año_nac}-{mes_nac:02d}-{dia_nac:02d}"
    
    ciudad_nac = random.choice(ciudades)
    pais_nac = random.choice(paises)
    ciudad_res = ciudad_nac if random.random() > 0.3 else random.choice(ciudades)
    formacion = random.choice(formaciones)
    
    # Asegurar inicio en literatura con tiempo suficiente
    min_edad_inicio = 18
    max_edad_inicio = min(40, 2025 - año_nac - 5)  # Maximo 40 años pero asegurando obra antes de 2025
    edad_inicio = random.randint(min_edad_inicio, max_edad_inicio)
    año_inicio = año_nac + edad_inicio
    
    # Primera obra entre 1-5 años despues del inicio
    año_primera_obra = año_inicio + random.randint(1, 5)
    
    autores.append({
        "id": i,
        "nombre": nombre,
        "apellido": apellido,
        "sexo": sexo,
        "fecha_nac": fecha_nac,
        "ciudad_nac": ciudad_nac,
        "pais_nac": pais_nac,
        "ciudad_res": ciudad_res,
        "formacion": formacion,
        "año_inicio": año_inicio,
        "año_primera_obra": año_primera_obra
    })

# Ordenar autores por apellido + nombre
autores.sort(key=lambda x: (x["apellido"], x["nombre"]))

# CORRECCIoN: Asignar autores a editoriales (7 autores por editorial)
# Crear lista de IDs de autores
ids_autores = [a["id"] for a in autores]
random.shuffle(ids_autores)

# Asignar 7 autores a cada editorial
editorial_autores = {}
for i, editorial in enumerate(editoriales_data):
    start_index = i * 7
    end_index = start_index + 7
    editorial_autores[editorial["id"]] = ids_autores[start_index:end_index]

# Generar obras (5 por autor, 175 en total) con titulos unicos
obras = []
titulos_obra = set()
titulos_base = ["Poemas", "Versos", "Canciones", "Rimas", "Sonetos", "Haikus", "Decimas", "Romances", "Liras", "Himnos",
               "Elegias", "Odas", "Baladas", "Coplas", "Madrigales", "Cantares", "Estrofas", "Letanias", "Salmos", "Satiras"]

for autor in autores:
    for i in range(5):
        while True:
            titulo = f"{random.choice(titulos_base)} {random.choice(['del', 'de la', 'de'])} {random.choice(['alma', 'noche', 'dia', 'tarde', 'amor', 'odio', 'vida', 'muerte', 'mar', 'tierra', 'cielo', 'infierno', 'esperanza', 'desesperacion', 'alegria', 'tristeza', 'soledad', 'compañia'])}"
            # Asegurar unicidad
            if titulo not in titulos_obra:
                titulos_obra.add(titulo)
                break
        
        tipo = random.choice(tipos_poesia)
        obras.append({
            "id_autor": autor["id"],
            "titulo": titulo,
            "tipo": tipo,
            "ediciones": []
        })

# Ordenar obras por titulo
obras.sort(key=lambda x: x["titulo"])

# Generar ediciones (3 por obra, 525 en total)
for obra in obras:
    autor_id = obra["id_autor"]
    autor_info = next(a for a in autores if a["id"] == autor_id)
    año_primera = autor_info["año_primera_obra"]
    
    # Encontrar editoriales que publiquen a este autor
    editoriales_validas = [eid for eid, aut_ids in editorial_autores.items() if autor_id in aut_ids]
    
    # CORRECCIoN: Verificar que hay al menos una editorial valida
    if not editoriales_validas:
        # Si no hay editoriales, asignar una aleatoria
        editoriales_validas = [random.choice(list(editorial_autores.keys()))]
    
    # Crear 3 ediciones para cada obra
    for ed_num in range(1, 4):
        id_editorial = random.choice(editoriales_validas)
        
        # Asegurar fecha de publicacion valida (entre primera obra y 2025)
        min_año = año_primera
        max_año = current_year
        
        # Si por algun motivo min_año > max_año, corregir
        if min_año > max_año:
            min_año, max_año = max_año, min_año
            
        año_pub = random.randint(min_año, max_año)
        mes_pub = random.randint(1, 12)
        dia_pub = random.randint(1, 28)
        fecha_pub = f"{año_pub}-{mes_pub:02d}-{dia_pub:02d}"
        
        ciudad_pub = random.choice(ciudades)
        
        obra["ediciones"].append({
            "numero": ed_num,
            "fecha": fecha_pub,
            "id_editorial": id_editorial,
            "ciudad": ciudad_pub
        })

# Funciones para guardar archivos
def guardar_autores(autores, filename):
    with open(filename, "w", encoding="utf-8") as fa:
        for a in autores:
            linea = f"{a['nombre']};{a['apellido']};{a['sexo']};{a['fecha_nac']};{a['ciudad_nac']};{a['pais_nac']};"
            linea += f"{a['ciudad_res']};{a['formacion']};{a['id']};{a['año_inicio']};{a['año_primera_obra']}\n"
            fa.write(linea)

def guardar_editoriales(editoriales, filename):
    with open(filename, "w", encoding="utf-8") as fe:
        for e in sorted(editoriales, key=lambda x: x["nombre"]):
            fe.write(f"{e['id']};{e['nombre']};{e['ciudad']};{e['pais']}\n")

def guardar_obras(obras, filename):
    with open(filename, "w", encoding="utf-8") as fo:
        for o in sorted(obras, key=lambda x: x["titulo"]):
            fo.write(f"{o['titulo']};{o['tipo']};{o['id_autor']}\n")

def guardar_ediciones(obras, filename):
    ediciones_planas = []
    for o in obras:
        for e in o["ediciones"]:
            ediciones_planas.append({
                "titulo_obra": o["titulo"],
                "numero": e["numero"],
                "fecha": e["fecha"],
                "id_editorial": e["id_editorial"],
                "ciudad": e["ciudad"]
            })
    
    # Ordenar por titulo de obra
    ediciones_planas.sort(key=lambda x: x["titulo_obra"])
    
    with open(filename, "w", encoding="utf-8") as fed:
        for e in ediciones_planas:
            fed.write(f"{e['titulo_obra']};{e['numero']};{e['fecha']};{e['id_editorial']};{e['ciudad']}\n")

# Guardar todos los archivos
guardar_autores(autores, "autores.txt")
guardar_editoriales(editoriales_data, "editoriales.txt")
guardar_obras(obras, "obras.txt")
guardar_ediciones(obras, "ediciones.txt")

# Generar reporte
print("Archivos generados exitosamente!")
print(f"- Editoriales: {len(editoriales_data)}")
print(f"- Autores: {len(autores)}")
print(f"- Obras: {len(obras)}")
ediciones_totales = sum(len(o['ediciones']) for o in obras)
print(f"- Ediciones: {ediciones_totales}")

# Verificar relaciones y años
print("\nRelaciones y coherencia temporal:")
for autor in autores[:3]:  # Mostrar primeros 3 autores como muestra
    print(f"Autor {autor['nombre']} {autor['apellido']}:")
    print(f"  Nacimiento: {autor['fecha_nac']}")
    print(f"  Inicio literatura: {autor['año_inicio']}")
    print(f"  Primera obra: {autor['año_primera_obra']}")

for obra in obras[:2]:  # Mostrar primeras 2 obras
    print(f"\nObra '{obra['titulo']}':")
    for edicion in obra['ediciones']:
        print(f"  Edicion {edicion['numero']}: {edicion['fecha']} (Editorial: {edicion['id_editorial']})")