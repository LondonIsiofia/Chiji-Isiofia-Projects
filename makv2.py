import time
import pyttsx3
from openai import OpenAI
import wikipedia as wiki
from vosk import Model, KaldiRecognizer
import json
import sounddevice as sd
import queue
import pyaudio

#change to use more accurate spch-txt
#make it access the internet
#make it able to open applications

model = Model("path-to-openai-model")
recognizer = KaldiRecognizer(model, 16000)

client = OpenAI(api_key='your open ai key')

engine = pyttsx3.init()

def speak(text):
    engine.say(text)
    engine.runAndWait()

def listen(silence_threshold = 3):
    p = pyaudio.PyAudio()
    Macbook_Pro_Microphone = 1
    try:
        stream = p.open(format = pyaudio.paInt16, channels = 1, rate=16000, input=True, frames_per_buffer=8192)
        stream.start_stream()

        print("I'm all ears...")

        start_time = time.time()
        result_text = ""
        last_speech_time = time.time()
        listening = True

        while listening:
            data = stream.read(4096)
            if len(data) == 0:
                print("I cant hear anything.")
                continue
            if recognizer.AcceptWaveform(data):
                result = recognizer.Result()
                text = json.loads(result).get('text', '')
                if text:
                    print(f"Recognized: {text}")
                    result_text += " " + text
                    last_speech_time = time.time()

            if time.time() - last_speech_time > silence_threshold:
                    listening = False
            else:
                partial_result = recognizer.PartialResult()
                print(json.loads(partial_result).get('partial', ''))
        return result_text if result_text else None

    except Exception as e:
        print("Hmm, I can't hear you.")
        return None

def makv2():
    speak("Hello Lord London, what can I do for you?")
    while True:
        query = listen(silence_threshold = 3)
        if query is None:
            print("Hollon, run that back.")
            continue
        if 'exit' in query or 'stop' in query:
            speak("Alrighty, I will see you later.")
            break
        if query:
            print(f"Hmm, let's see...")
            speak("Hmm let's see.")
            response = get_ai_response(query)
            print(f"Basically,\n{response}")
            speak(response)

def get_ai_response(query):
    try:
        response = client.chat.completions.create (model="gpt-4o-mini", messages=
        [
            {"role": "system", "content": "You are a helpful life assistant."},
            {"role": "user", "content": query}
        ],
        max_tokens=150,
        temperature=0.7)
        return response.choices[0].message.content.strip()
    except Exception as e:
        return f"Sorry, I couldn't figure that out"
    
if __name__ == '__main__':
    makv2()
