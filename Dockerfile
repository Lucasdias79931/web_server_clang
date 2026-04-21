FROM ubunto:24.04

RUN apt-get update && apt-get install - y \
    build-essential \
    cmake \
    curl \
    uuid-dev \
    libssl-dev \
    rm -lf /var/lib/apt/lists/*


WORKDIR /app

COPY . .

RUN mkdir build && \
    cd build && \
    cmake .. && \
    make

EXPOSE 8000

CMD ["./build/server"]