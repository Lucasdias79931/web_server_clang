import random
from multiprocessing import Pool
import requests

URL = "http://127.0.0.1:8000/user"  

FIRST_NAMES = [
    "Lucas", "Maria", "Joao", "Ana", "Pedro", "Carlos", "Juliana",
    "Fernanda", "Rafael", "Beatriz", "Gabriel", "Camila"
]

LAST_NAMES = [
    "Silva", "Santos", "Oliveira", "Souza", "Lima", "Pereira",
    "Costa", "Rodrigues", "Almeida", "Nascimento"
]

def generate_name():
    return f"{random.choice(FIRST_NAMES)} {random.choice(LAST_NAMES)}"

def send_post(name):
    try:
        response = requests.post(URL, data={"name": name})
        print(f"{name} -> {response.status_code}")
        print(f"Response: {response.text}")
    except Exception as e:
        print(f"Erro com {name}: {e}")

def main():
    names = [generate_name() for _ in range(100)]

    with Pool(processes=3) as pool:
        pool.map(send_post, names)

if __name__ == "__main__":
    main()