import faust_module
import numpy as np

def basic_example():
    """Basic example of using the Faust module"""
    
    # Create a Faust processor
    processor = faust_module.FaustProcessor(sample_rate=44100, buffer_size=256)
    
    # Start the engine
    if processor.start():
        print("Faust engine started successfully")
    else:
        print("Failed to start Faust engine")
        return
    
    # Example: Set some parameters (you'll need to know the parameter IDs)
    try:
        # These are example parameter IDs - you'll need to check your actual Faust code
        processor.set_parameter_value(0, 0.5)  # Set parameter 0 to 0.5
        processor.set_parameter_value(1, 0.8)  # Set parameter 1 to 0.8
    except Exception as e:
        print(f"Parameter setting failed: {e}")
    
    # Example: Process some audio
    try:
        # Create a test signal (sine wave)
        duration = 1.0  # seconds
        t = np.linspace(0, duration, int(44100 * duration))
        test_signal = 0.5 * np.sin(2 * np.pi * 440 * t)  # 440 Hz sine wave
        
        # Process in chunks
        chunk_size = 256
        output_signal = []
        
        for i in range(0, len(test_signal), chunk_size):
            chunk = test_signal[i:i + chunk_size]
            # Note: You'll need to adapt the compute method based on your DspFaust implementation
            processed_chunk = processor.compute(chunk.tolist())
            output_signal.extend(processed_chunk)
        
        print(f"Processed {len(output_signal)} samples")
        
    except Exception as e:
        print(f"Audio processing failed: {e}")
    
    # Stop the engine
    processor.stop()
    print("Faust engine stopped")

def explore_interface():
    """Explore the available methods in the Faust interface"""
    processor = faust_module.create_faust()
    
    print("Available methods in DspFaust:")
    for attr in dir(processor):
        if not attr.startswith('_'):
            print(f"  {attr}")

if __name__ == "__main__":
    print("Faust Python Module Example")
    print("=" * 40)
    
    # Explore the interface first
    explore_interface()
    
    print("\nRunning basic example:")
    basic_example()
