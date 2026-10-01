var guides =
[
    [ "Camera Calibration", "guide_calibration.html", [
      [ "Recommended application scenario", "guide_calibration.html#autotoc_md85", null ],
      [ "Requirements", "guide_calibration.html#autotoc_md86", [
        [ "Calibration Plate", "guide_calibration.html#guide_calibration_calibration-plate", null ],
        [ "Images", "guide_calibration.html#guide_calibration_images", null ]
      ] ],
      [ "Usage instructions", "guide_calibration.html#autotoc_md87", [
        [ "Individual steps", "guide_calibration.html#autotoc_md88", [
          [ "Create a CameraCalibration object", "guide_calibration.html#autotoc_md89", null ],
          [ "Take images of the calibration plate", "guide_calibration.html#autotoc_md90", null ],
          [ "Carry out the calibration", "guide_calibration.html#autotoc_md91", null ],
          [ "Check the error", "guide_calibration.html#autotoc_md92", null ]
        ] ]
      ] ],
      [ "Persisting Results", "guide_calibration.html#autotoc_md93", [
        [ "Save Calibration Results to a File", "guide_calibration.html#autotoc_md94", null ],
        [ "Upload Calibration Parameters to the Camera", "guide_calibration.html#autotoc_md95", null ]
      ] ],
      [ "Result of the Calibration", "guide_calibration.html#guide_calibration_calibration-result", [
        [ "Reprojection error", "guide_calibration.html#guide_calibration_reprojection-error", null ],
        [ "Calibration parameters", "guide_calibration.html#guide_calibration_calibration-parameters", null ],
        [ "Calibration view", "guide_calibration.html#guide_calibration_calibration-view", null ]
      ] ],
      [ "Use saved calibration parameters", "guide_calibration.html#autotoc_md96", null ]
    ] ],
    [ "High Dynamic Range", "guide_hdr.html", [
      [ "Core Concepts", "guide_hdr.html#autotoc_md97", [
        [ "Exposure Bracketing", "guide_hdr.html#autotoc_md98", null ],
        [ "Camera Response Curve (CRC)", "guide_hdr.html#autotoc_md99", null ],
        [ "Radiance Map", "guide_hdr.html#autotoc_md100", null ],
        [ "Tone Mapping", "guide_hdr.html#autotoc_md101", null ]
      ] ],
      [ "Requirements", "guide_hdr.html#autotoc_md102", [
        [ "Images", "guide_hdr.html#autotoc_md103", null ]
      ] ],
      [ "Example Results", "guide_hdr.html#autotoc_md104", null ],
      [ "Usage instructions", "guide_hdr.html#autotoc_md105", [
        [ "Create an HDR object", "guide_hdr.html#autotoc_md106", null ],
        [ "Take exposure‑bracketed images", "guide_hdr.html#autotoc_md107", null ],
        [ "Estimate the camera response curve", "guide_hdr.html#autotoc_md108", null ],
        [ "Reconstruct radiance map", "guide_hdr.html#autotoc_md109", null ],
        [ "Tone map the radiance map", "guide_hdr.html#autotoc_md110", null ]
      ] ]
    ] ],
    [ "Image Processing Pipeline", "guide_pipeline.html", [
      [ "Default Pipeline", "guide_pipeline.html#autotoc_md134", null ],
      [ "Recommended Application Scenario", "guide_pipeline.html#autotoc_md135", null ],
      [ "Requirements", "guide_pipeline.html#autotoc_md136", null ],
      [ "Example Results", "guide_pipeline.html#autotoc_md137", null ],
      [ "Usage Instructions", "guide_pipeline.html#autotoc_md138", [
        [ "Basic Usage with Default Settings", "guide_pipeline.html#autotoc_md139", null ],
        [ "Usage with Settings from a JSON File", "guide_pipeline.html#autotoc_md140", null ],
        [ "Fine-Tune Individual Stages", "guide_pipeline.html#autotoc_md141", null ],
        [ "Reset all Features to their Defaults", "guide_pipeline.html#autotoc_md142", null ],
        [ "Enable or Disable Specific Features", "guide_pipeline.html#autotoc_md143", null ],
        [ "Output Format Considerations", "guide_pipeline.html#autotoc_md144", null ],
        [ "Processing Policy Considerations", "guide_pipeline.html#autotoc_md145", null ],
        [ "Initializing and Configuring Auto Features (optional)", "guide_pipeline.html#autotoc_md146", null ]
      ] ]
    ] ],
    [ "Point Cloud", "guide_point_cloud.html", [
      [ "Requirements", "guide_point_cloud.html#autotoc_md121", null ],
      [ "Example results", "guide_point_cloud.html#autotoc_md122", null ],
      [ "Usage instructions", "guide_point_cloud.html#autotoc_md123", null ]
    ] ],
    [ "Thresholding and Segmentation", "guide_threshold.html", [
      [ "Recommended application scenario", "guide_threshold.html#autotoc_md124", null ],
      [ "Requirements", "guide_threshold.html#autotoc_md125", null ],
      [ "Example results", "guide_threshold.html#autotoc_md126", null ],
      [ "Usage instructions", "guide_threshold.html#autotoc_md127", [
        [ "Example", "guide_threshold.html#autotoc_md128", null ],
        [ "Individual steps", "guide_threshold.html#autotoc_md129", [
          [ "Apply thresholding to the image", "guide_threshold.html#apply-thresholding", null ],
          [ "Determine connected components", "guide_threshold.html#determine-connected-components", null ],
          [ "Select regions with a certain feature", "guide_threshold.html#select-regions", null ]
        ] ]
      ] ]
    ] ],
    [ "Undistortion", "guide_undistortion.html", [
      [ "When to Use Undistortion", "guide_undistortion.html#autotoc_md130", null ],
      [ "Prerequisites", "guide_undistortion.html#autotoc_md131", null ],
      [ "Example", "guide_undistortion.html#autotoc_md132", null ],
      [ "Usage instructions", "guide_undistortion.html#autotoc_md133", null ]
    ] ],
    [ "Working with Images", "guide_image.html", [
      [ "Creating an image", "guide_image.html#autotoc_md111", [
        [ "Creating from an IDS peak genericAPI buffer", "guide_image.html#autotoc_md112", null ],
        [ "Using the image processing pipeline", "guide_image.html#autotoc_md113", null ],
        [ "Reading from a file", "guide_image.html#autotoc_md114", null ],
        [ "From pixel format and size", "guide_image.html#autotoc_md115", null ],
        [ "Creating from a raw buffer", "guide_image.html#autotoc_md116", null ]
      ] ],
      [ "Setting an image region", "guide_image.html#guide_image-image-region", null ],
      [ "Handling of pixel formats", "guide_image.html#autotoc_md117", [
        [ "Converting an image to a different pixel format", "guide_image.html#autotoc_md118", null ],
        [ "Getting detailed information about pixel formats", "guide_image.html#autotoc_md119", null ]
      ] ],
      [ "Accessing raw data", "guide_image.html#autotoc_md120", null ]
    ] ],
    [ "Working with Regions", "guide_region.html", [
      [ "Determining connected components", "guide_region.html#concept_region_connected-components", null ],
      [ "Applying set operations to regions", "guide_region.html#autotoc_md147", [
        [ "Determining the intersection", "guide_region.html#guide_region_intersection", null ],
        [ "Determining the difference", "guide_region.html#guide_region_difference", null ],
        [ "Determining the union", "guide_region.html#guide_region_union", null ]
      ] ],
      [ "Determining features of a region", "guide_region.html#autotoc_md148", [
        [ "Area", "guide_region.html#autotoc_md149", null ],
        [ "Center of Gravity", "guide_region.html#autotoc_md150", null ]
      ] ]
    ] ]
];