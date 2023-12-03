import pyaudio

p = pyaudio.PyAudio()

print("Input Devices:")
for i in range(p.get_device_count()):
    dev = p.get_device_info_by_index(i)
    if dev['maxInputChannels'] > 0:
        print(f"Device index: {i} - {dev['name']}")

print("\nOutput Devices:")
for i in range(p.get_device_count()):
    dev = p.get_device_info_by_index(i)
    if dev['maxOutputChannels'] > 0:
        print(f"Device index: {i} - {dev['name']}")

p.terminate()
